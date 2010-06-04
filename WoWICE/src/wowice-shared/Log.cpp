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

#include "Common.h"
#include "Config/ConfigEnv.h"
#include "Log.h"
#include "NGLog.h"
#include <stdarg.h>

string FormatOutputString(const char * Prefix, const char * Description, bool useTimeStamp)
{

	char p[MAX_PATH];
	p[0] = 0;
	time_t t = time(NULL);
	tm * a = gmtime(&t);
	strcat(p, Prefix);
	strcat(p, "/");
	strcat(p, Description);
	if(useTimeStamp)
	{
		char ftime[100];
		snprintf(ftime, 100, "-%-4d-%02d-%02d %02d-%02d-%02d", a->tm_year+1900, a->tm_mon+1, a->tm_mday, a->tm_hour, a->tm_min, a->tm_sec);
		strcat(p, ftime);
	}

	strcat(p, ".log");
	return string(p);
}

createFileSingleton( oLog );
createFileSingleton(CLog);
initialiseSingleton( WorldLog );

SERVER_DECL time_t UNIXTIME;
SERVER_DECL tm g_localTime;

void oLog::outTime()
{
	time_t now;
	struct tm * timeinfo = NULL;
	char buffer[10];
	
	time( &now );
	timeinfo = localtime( &now );

	if( timeinfo != NULL )
	{
		strftime(buffer,10,"[%H:%M]",timeinfo);
		fprintf( m_file, buffer );
	}
}

void oLog::outString( const char * str, ... )
{
	if(m_fileLogLevel < 0 && m_screenLogLevel < 0)
		return;

	char buf[32768];
	va_list ap;

	va_start(ap, str);
	vsnprintf(buf, 32768, str, ap);
	va_end(ap);

	if(m_screenLogLevel >= 0)
	{
		printf(buf);
		putc('\n', stdout);
	}
	if(m_fileLogLevel >= 0 && m_file)
	{
		outTime();
		fprintf(m_file, buf);
		putc('\n', m_file);
	}
}

void oLog::outError( const char * err, ... )
{
	if(m_fileLogLevel < 1 && m_screenLogLevel < 1)
		return;

	char buf[32768];
	va_list ap;

	va_start(ap, err);
	vsnprintf(buf, 32768, err, ap);
	va_end(ap);

	if(m_screenLogLevel >= 1)
	{
#ifdef WIN32
		SetConsoleTextAttribute(stderr_handle, TRED);
#else
		puts(colorstrings[TRED]);
#endif
		fprintf(stderr, buf);
		putc('\n', stderr);
#ifdef WIN32
		SetConsoleTextAttribute(stderr_handle, TNORMAL);
#else
		puts(colorstrings[TNORMAL]);
#endif
	}
	if(m_fileLogLevel >= 1 && m_file)
	{
		outTime();
		fprintf(m_file, buf);
		putc('\n', m_file);
	}
}

void oLog::outBasic( const char * str, ... )
{
	if(m_fileLogLevel < 1 && m_screenLogLevel < 1)
		return;

	char buf[32768];
	va_list ap;

	va_start(ap, str);
	vsnprintf(buf, 32768, str, ap);
	va_end(ap);

	if(m_screenLogLevel >= 1)
	{
		printf(buf);
		putc('\n', stdout);
	}
	if(m_fileLogLevel >= 1 && m_file)
	{
		fprintf(m_file, buf);
		putc('\n', m_file);
	}
}

void oLog::outDetail( const char * str, ... )
{
	if(m_fileLogLevel < 2 && m_screenLogLevel < 2)
		return;

	char buf[32768];
	va_list ap;

	va_start(ap, str);
	vsnprintf(buf, 32768, str, ap);
	va_end(ap);

	if(m_screenLogLevel >= 2)
	{
		printf(buf);
		putc('\n', stdout);
	}
	if(m_fileLogLevel >= 2 && m_file)
	{
		outTime();
		fprintf(m_file, buf);
		putc('\n', m_file);
	}
}

void oLog::outDebug( const char * str, ... )
{
	if(m_fileLogLevel < 3 && m_screenLogLevel < 3)
		return;

	char buf[32768];
	va_list ap;

	va_start(ap, str);
	vsnprintf(buf, 32768, str, ap);
	va_end(ap);

	if(m_screenLogLevel >= 3)
	{
		printf(buf);
		putc('\n', stdout);
	}
	if(m_fileLogLevel >= 3 && m_file)
	{
		outTime();
		fprintf(m_file, buf);
		putc('\n', m_file);
	}
}

void oLog::outMenu( const char * str, ... )
{
	va_list ap;
	va_start(ap, str);
	vprintf( str, ap );
	va_end(ap);
	fflush(stdout);
}

void oLog::Init(int32 fileLogLevel, int32 screenLogLevel)
{
	m_screenLogLevel = screenLogLevel;
	m_fileLogLevel = fileLogLevel;

	// get error handle
#ifdef WIN32
	stderr_handle = GetStdHandle(STD_ERROR_HANDLE);
	stdout_handle = GetStdHandle(STD_OUTPUT_HANDLE);
#endif
}

void oLog::SetScreenLoggingLevel(int32 level)
{
	m_screenLogLevel = level;
}

void oLog::SetFileLoggingLevel(int32 level, const char *filename)
{
	m_fileLogLevel = level;

	if (m_fileLogLevel >= 0)
	{
		m_file = fopen(filename, "a");
		if (m_file == NULL)
		{
			fprintf(stderr, "%s: Error opening '%s': %s\n", __FUNCTION__, filename, strerror(errno));
		}
	}
}

void SessionLogWriter::write(const char* format, ...)
{
	if(!m_file)
		return;

	char out[32768];
	va_list ap;

	va_start(ap, format);
	time_t t = time(NULL);
	tm* aTm = localtime(&t);
	sprintf(out, "[%-4d-%02d-%02d %02d:%02d:%02d] ",aTm->tm_year+1900,aTm->tm_mon+1,aTm->tm_mday,aTm->tm_hour,aTm->tm_min,aTm->tm_sec);
	size_t l = strlen(out);
	vsnprintf(&out[l], 32768 - l, format, ap);
	fprintf(m_file, "%s\n", out);
	va_end(ap);
}

WorldLog::WorldLog()
{
	bEnabled = false;
	m_file= NULL;

	if (Config.MainConfig.GetBoolDefault("LogLevel", "World", false))
	{
		Log.Notice("WorldLog", "Enabling packetlog output to \"world.log\"");
		Enable();
	} else {
		Disable();
	}
}

void WorldLog::Enable()
{
	if(bEnabled)
		return;

	bEnabled = true;
	if(m_file != NULL)
	{
		Disable();
		bEnabled=true;
	}
	m_file = fopen("world.log", "a");
}

void WorldLog::Disable()
{
	if(!bEnabled)
		return;

	bEnabled = false;
	if(!m_file)
		return;

	fflush(m_file);
	fclose(m_file);
	m_file= NULL;
}

WorldLog::~WorldLog()
{
if (m_file)
	{
		fclose(m_file);
		m_file = NULL;
	}
}

void oLog::outColor(uint8 colorcode, const char * str, ...)
{
	if( !str ) return;

	va_list ap;
	va_start(ap, str);
#ifdef WIN32
	SetConsoleTextAttribute(stdout_handle, colorcode);
#else
	printf(colorstrings[colorcode]);
#endif
	vprintf( str, ap );
	fflush(stdout);
	va_end(ap);
}

void SessionLogWriter::Open()
{
	m_file = fopen(m_filename, "a");
}

void SessionLogWriter::Close()
{
	if(!m_file) return;
	fflush(m_file);
	fclose(m_file);
	m_file= NULL;
}

SessionLogWriter::SessionLogWriter(const char * filename, bool open)
{
	m_filename = strdup(filename);
	m_file= NULL;
	if(open)
		Open();
}

SessionLogWriter::~SessionLogWriter()
{
	if(m_file)
		Close();

	free(m_filename);
}