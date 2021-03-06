/*
 * This program is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation, either version 3 of the License, or (at your option) any later
 * version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE. See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "LogonStdAfx.h"
#include <signal.h>
#include "svn_revision.h"
#ifndef WIN32
#include <sys/resource.h>
#endif
#include "../wowice-shared/wowice_getopt.h"

#define BANNER "WoWICE %s r%u/%s-%s (%s) :: Logon Server"

#ifndef WIN32
#include <sched.h>
#endif

// Database impl
Database * sLogonSQL;
initialiseSingleton(LogonServer);
bool mrunning = true;
Mutex _authSocketLock;
set<AuthSocket*> _authSockets;

/*** Signal Handler ***/
void _OnSignal(int s)
{
	switch (s)
	{
#ifndef WIN32
	case SIGHUP:
	   {
		   sLog.outString("Received SIGHUP signal, reloading accounts.");
		   AccountMgr::getSingleton().ReloadAccounts(true);
	   }break;
#endif
	case SIGINT:
	case SIGTERM:
	case SIGABRT:
#ifdef _WIN32
	case SIGBREAK:
#endif
		mrunning = false;
		break;
	}

	signal(s, _OnSignal);
}

int main(int argc, char** argv)
{
#ifndef WIN32
	rlimit rl;
	if (getrlimit(RLIMIT_CORE, &rl) == -1)
		printf("getrlimit failed. This could be problem.\n");
	else
	{
		rl.rlim_cur = rl.rlim_max;
		if (setrlimit(RLIMIT_CORE, &rl) == -1)
			printf("setrlimit failed. Server may not save core.dump files.\n");
	}
#endif

	new LogonServer;

	// Run!
	LogonServer::getSingleton( ).Run(argc, argv);
	delete LogonServer::getSingletonPtr();
}


/**
  * Initialises the logon database
  *
  * Reads the configs\logon.conf file and parses the <LogonDatabase> tag
  *
  * Any errors in this file, such as a missing parameter should be caught 
  * and the user notified in an intelligent way
  *
  * If no errors are found, the database is initialized
  **/
bool startdb()
{
	string lhostname, lusername, lpassword, ldatabase;
	int lport = 0;
	int ltype = 1;
	// Configure Main Database

	bool result;

	// Set up reusable parameter checks for each parameter
	// Note that the Config.MainConfig.Get[$type] methods returns boolean value and not $type

	bool existsUsername = Config.MainConfig.GetString("LogonDatabase", "Username", &lusername);
	bool existsPassword = Config.MainConfig.GetString("LogonDatabase", "Password", &lpassword);
	bool existsHostname = Config.MainConfig.GetString("LogonDatabase", "Hostname", &lhostname);
	bool existsName     = Config.MainConfig.GetString("LogonDatabase", "Name",     &ldatabase);
	bool existsPort     = Config.MainConfig.GetInt(   "LogonDatabase", "Port",     &lport    );
	bool existsType     = Config.MainConfig.GetInt(   "LogonDatabase", "Type",     &ltype    );

	// Configure Logon Database...

	// logical AND every parameter to ensure we catch any error
	result = existsUsername && existsPassword && existsHostname && existsName && existsPort && existsType;

	if( !result )
	{
		//Build informative error message
		//Built as one string and then printed rather than calling sLog.outString(...) for every line,
		//  as experiments has seen other thread write to the console inbetween calls to sLog.outString(...)
		//  resulting in unreadable error messages.
		//If the <LogonDatabase> tag is malformed, all parameters will fail, and a different error message is given

		string errorMessage = "sql: Certain <LogonDatabase> parameters not found in configs\\logon.conf \r\n";
		if( !(existsHostname || existsUsername || existsPassword  ||  
			  existsName     || existsPort     || existsType) )
		{
			errorMessage += "  Double check that you have remembered the entire <LogonDatabase> tag.\r\n";
			errorMessage += "  All parameters missing. It is possible you forgot the first '<' character.\r\n";
		}
		else
		{
			errorMessage +=                        "  Missing paramer(s):\r\n";
			if( !existsHostname ){ errorMessage += "    Hostname\r\n" ; }
			if( !existsUsername ){ errorMessage += "    Username\r\n" ; }
			if( !existsPassword ){ errorMessage += "    Password\r\n" ; }
			if( !existsName     ){ errorMessage += "    Name\r\n"; }
			if( !existsPort     ){ errorMessage += "    Port\r\n"; }
			if( !existsType     ){ errorMessage += "    Type\r\n"; }
		}

		sLog.outString( errorMessage.c_str());
		return false;
	}

	sLog.SetScreenLoggingLevel(Config.MainConfig.GetIntDefault("LogLevel", "Screen", 0));
	Log.log_level = Config.MainConfig.GetIntDefault("LogLevel", "Screen", 0);
	sLog.SetFileLoggingLevel(Config.MainConfig.GetIntDefault("LogLevel", "File", -1), "logonserver.log");
	sLogonSQL = Database::CreateDatabaseInterface( ltype );

	// Initialize it
	if(!sLogonSQL->Initialize(lhostname.c_str(), (unsigned int)lport, lusername.c_str(),
		lpassword.c_str(), ldatabase.c_str(), Config.MainConfig.GetIntDefault("LogonDatabase", "ConnectionCount", 5),
		16384))
	{
		sLog.outError("sql: Logon database initialization failed. Exiting.");
		return false;
	}

	return true;
}

#define DEF_VALUE_NOT_SET 0xDEADBEEF


Mutex m_allowedIpLock;
vector<AllowedIP> m_allowedIps;
vector<AllowedIP> m_allowedModIps;

bool IsServerAllowed(unsigned int IP)
{
	m_allowedIpLock.Acquire();
	for(vector<AllowedIP>::iterator itr = m_allowedIps.begin(); itr != m_allowedIps.end(); ++itr)
	{
		if( ParseCIDRBan(IP, itr->IP, itr->Bytes) )
		{
			m_allowedIpLock.Release();
			return true;
		}
	}
	m_allowedIpLock.Release();
	return false;
}

bool IsServerAllowedMod(unsigned int IP)
{
	m_allowedIpLock.Acquire();
	for(vector<AllowedIP>::iterator itr = m_allowedModIps.begin(); itr != m_allowedModIps.end(); ++itr)
	{
		if( ParseCIDRBan(IP, itr->IP, itr->Bytes) )
		{
			m_allowedIpLock.Release();
			return true;
		}
	}
	m_allowedIpLock.Release();
	return false;
}

bool Rehash()
{
#ifdef WIN32
	char * config_file = "configs/logon.conf";
#else
	char * config_file = (char*)CONFDIR "/logon.conf";
#endif
	if(!Config.MainConfig.SetSource(config_file))
	{
		printf("Config file could not be rehashed.\n");
		return false;
	}

	// re-set the allowed server IP's
	string ips = Config.MainConfig.GetStringDefault("LogonServer", "AllowedIPs", "");
	string ipsmod = Config.MainConfig.GetStringDefault("LogonServer", "AllowedModIPs", "");

	vector<string> vips = StrSplit(ips, " ");
	vector<string> vipsmod = StrSplit(ips, " ");

	m_allowedIpLock.Acquire();
	m_allowedIps.clear();
	m_allowedModIps.clear();
	vector<string>::iterator itr;
	for(itr = vips.begin(); itr != vips.end(); ++itr)
	{
		string::size_type i = itr->find("/");
		if( i == string::npos )
		{
			printf("IP: %s could not be parsed. Ignoring\n", itr->c_str());
			continue;
		}

		string stmp = itr->substr(0, i);
		string smask = itr->substr(i+1);

		unsigned int ipraw = MakeIP(stmp.c_str());
		unsigned char ipmask = (char)atoi(smask.c_str());
		if( ipraw == 0 || ipmask == 0 )
		{
			printf("IP: %s could not be parsed. Ignoring\n", itr->c_str());
			continue;
		}

		AllowedIP tmp;
		tmp.Bytes = ipmask;
		tmp.IP = ipraw;
		m_allowedIps.push_back(tmp);
	}

	for(itr = vipsmod.begin(); itr != vipsmod.end(); ++itr)
	{
		string::size_type i = itr->find("/");
		if( i == string::npos )
		{
			printf("IP: %s could not be parsed. Ignoring\n", itr->c_str());
			continue;
		}

		string stmp = itr->substr(0, i);
		string smask = itr->substr(i+1);

		unsigned int ipraw = MakeIP(stmp.c_str());
		unsigned char ipmask = (char)atoi(smask.c_str());
		if( ipraw == 0 || ipmask == 0 )
		{
			printf("IP: %s could not be parsed. Ignoring\n", itr->c_str());
			continue;
		}

		AllowedIP tmp;
		tmp.Bytes = ipmask;
		tmp.IP = ipraw;
		m_allowedModIps.push_back(tmp);
	}

	if( InformationCore::getSingletonPtr() != NULL )
		sInfoCore.CheckServers();

	m_allowedIpLock.Release();

	return true;
}


void LogonServer::Run(int argc, char ** argv)
{
	UNIXTIME = time(NULL);
	g_localTime = *localtime(&UNIXTIME);
#ifdef WIN32
	char * config_file = "configs/logon.conf";
#else
	char * config_file = (char*)CONFDIR "/logon.conf";
#endif
	int file_log_level = DEF_VALUE_NOT_SET;
	int screen_log_level = DEF_VALUE_NOT_SET;
	int do_check_conf = 0;
	int do_version = 0;

	struct wowice_option longopts[] =
	{
		{ "checkconf",			wowice_no_argument,				&do_check_conf,			1		},
		{ "screenloglevel",		wowice_required_argument,		&screen_log_level,		1		},
		{ "fileloglevel",		wowice_required_argument,		&file_log_level,		1		},
		{ "version",			wowice_no_argument,				&do_version,			1		},
		{ "conf",				wowice_required_argument,		NULL,					'c'		},
		{ 0, 0, 0, 0 }
	};

	int c;
	while ((c = wowice_getopt_long_only(argc, argv, ":f:", longopts, NULL)) != -1)
	{
		switch (c)
		{
		case 'c':
			/* Log filename was set */
			config_file = new char[strlen(wowice_optarg)];
			strcpy(config_file,wowice_optarg);
			break;
		case 0:
			break;
		default:
			sLog.m_fileLogLevel = -1;
			sLog.m_screenLogLevel = 3;
			printf("Usage: %s [--checkconf] [--screenloglevel <level>] [--fileloglevel <level>] [--conf <filename>] [--version]\n", argv[0]);
			return;
		}
	}

	// Startup banner
	if(!do_version && !do_check_conf)
	{
		sLog.Init(-1, 3);
	}
	else
	{
		sLog.m_fileLogLevel = -1;
		sLog.m_screenLogLevel = 3;
	}
	
	sLog.outString(BANNER, BUILD_TAG, BUILD_REVISION, CONFIG, PLATFORM_TEXT, ARCH);
	Log.Color(TBLUE);
	printf("\nCopyright (C) 2009 WoWICE. http://code.google.com/p/wowice/\n");
	printf("This program is free software: you can redistribute it and/or modify\n");
	printf("it under the terms of the GNU Affero General Public License as published by\n");
	printf("the Free Software Foundation, either version 3 of the License, or\n");
	printf("any later version.\n");
	printf("This program is distributed in the hope that it will be useful,\n");
	printf("but WITHOUT ANY WARRANTY; without even the implied warranty of\n");
	printf("MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n");
	printf("GNU Affero General Public License for more details.\n");
	printf(" Website: http://code.google.com/p/wowice/  	\n");
	printf(" SVN: http://wowice.googlecode.com/svn/trunk/   \n");
	printf(" Have fun!                                      \n");
	Log.Line();
#ifdef REPACK
	sLog.outString("Repack: %s | Author: %s | %s\n", REPACK, REPACK_AUTHOR, REPACK_WEBSITE);
#endif
	sLog.outString("==============================================================================");
	sLog.outString("");
	if(do_version)
		return;

	if(do_check_conf)
	{
		printf("Checking config file: %s\n", config_file);
		if(Config.MainConfig.SetSource(config_file, true))
			printf("  Passed without errors.\n");
		else
			printf("  Encountered one or more errors.\n");
		/* Remved useless die directive */
		/*
		string die;
		if(Config.MainConfig.GetString("die", "msg", &die) || Config.MainConfig.GetString("die2", "msg", &die))
			printf("Die directive received: %s", die.c_str());
		*/
		return;
	}

	/* set new log levels */
	if( screen_log_level != (int)DEF_VALUE_NOT_SET )
		sLog.SetScreenLoggingLevel(screen_log_level);
	
	if( file_log_level != (int)DEF_VALUE_NOT_SET )
		sLog.SetFileLoggingLevel(file_log_level, "logonserver.log");

	sLog.outString("The key combination <Ctrl-C> will safely shut down the server at any time.");
	sLog.outString("");
	Log.Notice("System","Initializing Random Number Generators...");

	Log.Notice("Config", "Loading Config Files...");
	if(!Rehash())
		return;

	Log.Notice("ThreadMgr", "Starting...");
	ThreadPool.Startup();
   
	if(!startdb())
		return;

	Log.Notice("AccountMgr", "Starting...");
	new AccountMgr;
	new IPBanner;

	Log.Notice("InfoCore", "Starting...");
	new InformationCore;

	new PatchMgr;
	Log.Notice("AccountMgr", "Precaching accounts...");
	sAccountMgr.ReloadAccounts(true);
	Log.Notice("AccountMgr", "%u accounts are loaded and ready.", sAccountMgr.GetCount());
	Log.Line();


	// Spawn periodic function caller thread for account reload every 10mins
	int atime = Config.MainConfig.GetIntDefault("Rates", "AccountRefresh",600);
	atime *= 1000;
	//SpawnPeriodicCallThread(AccountMgr, AccountMgr::getSingletonPtr(), &AccountMgr::ReloadAccountsCallback, time);
	PeriodicFunctionCaller<AccountMgr> * pfc = new PeriodicFunctionCaller<AccountMgr>(AccountMgr::getSingletonPtr(), &AccountMgr::ReloadAccountsCallback, atime);
	ThreadPool.ExecuteTask(pfc);

	// Load conf settings..
	uint32 cport = Config.MainConfig.GetIntDefault("Listen", "RealmListPort", 3724);
	uint32 sport = Config.MainConfig.GetIntDefault("Listen", "ServerPort", 8093);
	//uint32 threadcount = Config.MainConfig.GetIntDefault("Network", "ThreadCount", 5);
	//uint32 threaddelay = Config.MainConfig.GetIntDefault("Network", "ThreadDelay", 20);
	string host = Config.MainConfig.GetStringDefault("Listen", "Host", "0.0.0.0");
	string shost = Config.MainConfig.GetStringDefault("Listen", "ISHost", host.c_str());

	/* Due to many people's inability to cope with us being out-of-sync with retail sometimes we were forced to hardcode this
	min_build = Config.MainConfig.GetIntDefault("Client", "MinBuild", 6180);
	max_build = Config.MainConfig.GetIntDefault("Client", "MaxBuild", 6999);
	*/

	min_build = LOGON_MINBUILD;
	max_build = LOGON_MAXBUILD;

	string logon_pass = Config.MainConfig.GetStringDefault("LogonServer", "RemotePassword", "r3m0t3b4d");
	Sha1Hash hash;
	hash.UpdateData(logon_pass);
	hash.Finalize();
	memcpy(sql_hash, hash.GetDigest(), 20);
	
	ThreadPool.ExecuteTask(new LogonConsoleThread);

	new SocketMgr;
	new SocketGarbageCollector;
	sSocketMgr.SpawnWorkerThreads();

	ListenSocket<AuthSocket> * cl = new ListenSocket<AuthSocket>(host.c_str(), cport);
	ListenSocket<LogonCommServerSocket> * sl = new ListenSocket<LogonCommServerSocket>(shost.c_str(), sport);

	// Spawn auth listener
	// Spawn interserver listener
	bool authsockcreated = cl->IsOpen();
	bool intersockcreated = sl->IsOpen();
#ifdef WIN32
	if(authsockcreated)
		ThreadPool.ExecuteTask(cl);
	if(intersockcreated)
		ThreadPool.ExecuteTask(sl);
#endif
	// hook signals
	sLog.outString("Hooking signals...");
	signal(SIGINT, _OnSignal);
	signal(SIGTERM, _OnSignal);
	signal(SIGABRT, _OnSignal);
#ifdef _WIN32
	signal(SIGBREAK, _OnSignal);
#else
	signal(SIGHUP, _OnSignal);
#endif

		/* write pid file */
	FILE * fPid = fopen("logonserver.pid", "w");
	if(fPid)
	{
		uint32 pid;
#ifdef WIN32
		pid = GetCurrentProcessId();
#else
		pid = getpid();
#endif
		fprintf(fPid, "%u", (unsigned int)pid);
		fclose(fPid);
	}
	uint32 loop_counter = 0;
	//ThreadPool.Gobble();
	sLog.outString("Success! Ready for connections");
	while(mrunning && authsockcreated && intersockcreated)
	{
		if(!(++loop_counter % 20))	 // 20 seconds
			CheckForDeadSockets();

		if(!(loop_counter%300))	// 5mins
			ThreadPool.IntegrityCheck();

		if(!(loop_counter%5))
		{
			sInfoCore.TimeoutSockets();
			sSocketGarbageCollector.Update();
			CheckForDeadSockets();			  // Flood Protection
			UNIXTIME = time(NULL);
			g_localTime = *localtime(&UNIXTIME);
		}

		PatchMgr::getSingleton().UpdateJobs();
		Sleep(1000);
	}

	sLog.outString("Shutting down...");
        signal(SIGINT, 0);
        signal(SIGTERM, 0);
        signal(SIGABRT, 0);
#ifdef _WIN32
        signal(SIGBREAK, 0);
#else
        signal(SIGHUP, 0);
#endif

	pfc->kill();

	cl->Close();
	sl->Close();
	sSocketMgr.CloseAll();
#ifdef WIN32
	sSocketMgr.ShutdownThreads();
#endif
	sLogonConsole.Kill();
	delete LogonConsole::getSingletonPtr();

	// kill db
	sLog.outString("Waiting for database to close..");
	sLogonSQL->EndThreads();
	sLogonSQL->Shutdown();
	delete sLogonSQL;

	ThreadPool.Shutdown();

	// delete pid file
	remove("logonserver.pid");

	delete AccountMgr::getSingletonPtr();
	delete InformationCore::getSingletonPtr();
	delete PatchMgr::getSingletonPtr();
	delete IPBanner::getSingletonPtr();
	delete SocketMgr::getSingletonPtr();
	delete SocketGarbageCollector::getSingletonPtr();
	delete pfc;
	delete cl;
	delete sl;
	printf("Shutdown complete.\n");
}

void OnCrash(bool Terminate)
{

}

void LogonServer::CheckForDeadSockets()
{
	_authSocketLock.Acquire();
	time_t t = time(NULL);
	time_t diff;
	set<AuthSocket*>::iterator itr = _authSockets.begin();
	set<AuthSocket*>::iterator it2;
	AuthSocket * s;

	for(itr = _authSockets.begin(); itr != _authSockets.end();)
	{
		it2 = itr;
		s = (*it2);
		++itr;

		diff = t - s->GetLastRecv();
		if(diff > 300)		   // More than 5mins
		{
			_authSockets.erase(it2);
			s->removedFromSet = true;
			s->Disconnect();
		}
	}
	_authSocketLock.Release();
}