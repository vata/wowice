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

#ifndef __WORLD_H
#define __WORLD_H

#define IS_INSTANCE( a ) ( ( a > 1 ) && ( a != 530 ) && ( a != 571 ) )

class Object;
class WorldPacket;
class WorldSession;
class Unit;
class Creature;
class GameObject;
class DynamicObject;
class Player;
class EventableObjectHolder;
class MapMgr;
class Battleground;

enum Rates
{
	RATE_HEALTH=0,// hp regen
	RATE_POWER1,  // mp regen
	RATE_POWER2,  // rage (rate unused)
	RATE_POWER3,  // focus regen (pets)
	RATE_POWER4,  // energy regen
//	RATE_POWER5,  // happiness (pets; rate unused)
//	RATE_POWER6,  // what is this? (rate unused)
	RATE_POWER7,  // runic power (rate unused)
	RATE_DROP0, // separate rates for each quality level
	RATE_DROP1,
	RATE_DROP2,
	RATE_DROP3,
	RATE_DROP4,
	RATE_DROP5,
	RATE_DROP6,
	RATE_MONEY,
	RATE_XP,
	RATE_RESTXP,
	RATE_QUESTXP,
	RATE_EXPLOREXP,
	RATE_HONOR,
	RATE_QUESTREPUTATION,
	RATE_KILLREPUTATION,
	RATE_SKILLCHANCE,
	RATE_SKILLRATE,
	RATE_ARENAPOINTMULTIPLIER2X,
	RATE_ARENAPOINTMULTIPLIER3X,
	RATE_ARENAPOINTMULTIPLIER5X,
	MAX_RATES
};		

enum IntRates
{
	INTRATE_SAVE=0,
	INTRATE_COMPRESSION,
	INTRATE_PVPTIMER,
	MAX_INTRATES
};


enum EnviromentalDamage
{
	DAMAGE_EXHAUSTED = 0,
	DAMAGE_DROWNING = 1,
	DAMAGE_FALL = 2,
	DAMAGE_LAVA = 3,
	DAMAGE_SLIME = 4,
	DAMAGE_FIRE = 5
};


// ServerMessages.dbc
enum ServerMessageType
{
	SERVER_MSG_SHUTDOWN_TIME	  = 1,
	SERVER_MSG_RESTART_TIME	   = 2,
	SERVER_MSG_STRING			 = 3,
	SERVER_MSG_SHUTDOWN_CANCELLED = 4,
	SERVER_MSG_RESTART_CANCELLED  = 5
};

enum WorldMapInfoFlag
{
	WMI_INSTANCE_ENABLED   = 0x1,
	WMI_INSTANCE_WELCOME   = 0x2,
	WMI_INSTANCE_ARENA = 0x4,
	WMI_INSTANCE_XPACK_01  = 0x8, //The Burning Crusade expansion
	WMI_INSTANCE_XPACK_02  = 0x10, //Wrath of the Lich King expansion
};

enum AccountFlags
{
	ACCOUNT_FLAG_VIP		 = 0x1,
	ACCOUNT_FLAG_NO_AUTOJOIN = 0x2,
	//ACCOUNT_FLAG_XTEND_INFO  = 0x4,
	ACCOUNT_FLAG_XPACK_01	= 0x8,
	ACCOUNT_FLAG_XPACK_02	= 0x10,
};

#pragma pack(push,1)
struct MapInfo
{
	uint32 mapid;
	uint32 screenid;
	uint32 type;
	uint32 playerlimit;
	uint32 minlevel;
	uint32 minlevel_heroic;
	float repopx;
	float repopy;
	float repopz;
	uint32 repopmapid;
	char * name;
	uint32 flags;
	uint32 cooldown;
    uint32 lvl_mod_a;
	uint32 required_quest;
	uint32 required_item;
	uint32 heroic_key_1;
	uint32 heroic_key_2;
	float update_distance;
	uint32 checkpoint_id;

	bool HasFlag(uint32 flag)
	{
		return (flags & flag) != 0;
	}
};

#pragma pack(pop)

enum REALM_TYPE
{
    REALM_PVE = 0,
    REALM_PVP = 1,
};
struct AreaTable;

class BasicTaskExecutor : public ThreadBase
{
	CallbackBase * cb;
	uint32 priority;
public:
	BasicTaskExecutor(CallbackBase * Callback, uint32 Priority) : cb(Callback), priority(Priority) {}
	~BasicTaskExecutor() { delete cb; }
	bool run();
};

class Task
{
	CallbackBase * _cb;
public:
	Task(CallbackBase * cb) : _cb(cb), completed(false), in_progress(false) {}
	~Task() { delete _cb; }
	bool completed;
	bool in_progress;
	void execute();
};

struct CharacterLoaderThread : public ThreadBase
{
#ifdef WIN32
	HANDLE hEvent;
#else
	pthread_cond_t cond;
	pthread_mutex_t mutex;
#endif
	bool running;
public:
	CharacterLoaderThread();
	~CharacterLoaderThread();
	void OnShutdown();
	bool run();
};

class TaskList
{
	set<Task*> tasks;
	Mutex queueLock;
public:
	Task * GetTask();
	void AddTask(Task* task);
	void RemoveTask(Task * task)
	{
		queueLock.Acquire();
		tasks.erase(task);
		queueLock.Release();
	}

	void spawn();
	void kill();

	void wait();
	void waitForThreadsToExit();
	uint32 thread_count;
	bool running;

	Mutex tcMutex;
	void incrementThreadCount()
	{
		tcMutex.Acquire();
		++thread_count;
		tcMutex.Release();
	}

	void decrementThreadCount()
	{
		tcMutex.Acquire();
		--thread_count;
		tcMutex.Release();
	}
};

enum BasicTaskExecutorPriorities
{
	BTE_PRIORITY_LOW		= 0,
	BTE_PRIORITY_MED		= 1,
	BTW_PRIORITY_HIGH	   = 2,
};

class TaskExecutor : public ThreadBase
{
	TaskList * starter;
public:
	TaskExecutor(TaskList * l) : starter(l) { l->incrementThreadCount(); }
	~TaskExecutor() { starter->decrementThreadCount(); }

	bool run();
};

class WorldSocket;

// Slow for remove in middle, oh well, wont get done much.
typedef std::list<WorldSocket*> QueueSet;
typedef set<WorldSession*> SessionSet;

class SERVER_DECL World : public Singleton<World>, public EventableObject
{
private:
	uint32 HordePlayers;
	uint32 AlliancePlayers;

public:
	WoWICE_INLINE uint32 getHordePlayerCount() { return HordePlayers; }
	WoWICE_INLINE uint32 getAlliancePlayerCount() { return AlliancePlayers; }
	WoWICE_INLINE uint32 getPlayerCount() { return (HordePlayers + AlliancePlayers); }
	WoWICE_INLINE void resetPlayerCount() { HordePlayers = AlliancePlayers = 0; }
	WoWICE_INLINE void incrementPlayerCount(uint32 faction)
	{
		if( faction == 1 )
			HordePlayers++;
		else
			AlliancePlayers++;
	}
	WoWICE_INLINE void decrementPlayerCount(uint32 faction)
	{
		if( faction == 1 )
			HordePlayers--;
		else
			AlliancePlayers--;
	}

// ToDo: Encapsulate below this point
public:
	World();
	~World();

	/** Reloads the config and sets all of the setting variables 
	 */
	void Rehash(bool load);

	void CleanupCheaters();
	WorldSession* FindSession(uint32 id);
	WorldSession* FindSessionByName(const char *);
	void AddSession(WorldSession *s);
	void RemoveSession(uint32 id);

	void AddGlobalSession(WorldSession *session);
	void RemoveGlobalSession(WorldSession *session);
	void DeleteSession(WorldSession *session);

	WoWICE_INLINE size_t GetSessionCount() const { return m_sessions.size(); }
	uint32 GetNonGmSessionCount();
	WoWICE_INLINE size_t GetQueueCount() { return mQueuedSessions.size(); }
	void GetStats(uint32 * GMCount, float * AverageLatency);

	WoWICE_INLINE uint32 GetPlayerLimit() const { return m_playerLimit; }
	void SetPlayerLimit(uint32 limit) { m_playerLimit = limit; }

	WoWICE_INLINE bool getAllowMovement() const { return m_allowMovement; }
	void SetAllowMovement(bool allow) { m_allowMovement = allow; }
	WoWICE_INLINE bool getGMTicketStatus() { return m_gmTicketSystem; };
	bool toggleGMTicketStatus()
	{
		m_gmTicketSystem = !m_gmTicketSystem;
		return m_gmTicketSystem;
	};

	WoWICE_INLINE std::string getGmClientChannel() { return GmClientChannel; }

	void SetMotd(const char *motd) { m_motd = motd; }
	WoWICE_INLINE const char* GetMotd() const { return m_motd.c_str(); }

	WoWICE_INLINE time_t GetGameTime() const { return m_gameTime; }

	bool SetInitialWorldSettings();

	void SendWorldText(const char *text, WorldSession *self = 0);
	void SendWorldWideScreenText(const char *text, WorldSession *self = 0);
	void SendGlobalMessage(WorldPacket *packet, WorldSession *self = 0);
	void SendZoneMessage(WorldPacket *packet, uint32 zoneid, WorldSession *self = 0);
	void SendInstanceMessage(WorldPacket *packet, uint32 instanceid, WorldSession *self = 0);
	void SendFactionMessage(WorldPacket *packet, uint8 teamId);
	void SendGamemasterMessage(WorldPacket *packet, WorldSession *self = 0);
	void SendGMWorldText(const char* text, WorldSession *self = 0);
	void SendBCMessageByID(uint32 id);
	void SendLocalizedWorldText(bool wide,const char * format, ...);

	WoWICE_INLINE void SetStartTime(uint32 val) { m_StartTime = val; }
	WoWICE_INLINE uint32 GetUptime(void) { return (uint32)UNIXTIME - m_StartTime; }
	WoWICE_INLINE uint32 GetStartTime(void) { return m_StartTime; }
	std::string GetUptimeString();
	// cebernic: textfilter,no fast,but works:D ...
	WoWICE_INLINE std::string SessionLocalizedTextFilter(WorldSession* _session,const char*text)
	{
			std::string opstr=string(text);
			std::string::iterator t= opstr.begin();
			std::string temp;
			int found = 0;
			std::string num;
			while ( t!=opstr.end() )
			{
				if ( (char)(*t)=='{' && strlen(  (char*) &(*t) )>1  ){ // find and no end :D
					found++;
					++t;
					continue;
				}
				if ( found==1 ) {
					if ( (char)(*t)=='}' ) found++;
					else num.push_back(*t);
				}
				if ( found ) // get the flag and doing my work and skip pushback.
				{
					if ( found==2 ) 
					{
						temp += _session->LocalizedWorldSrv((uint32) atoi((char*)num.c_str()) );
						found=0;
						num.clear();
					}
				}
				else temp.push_back(*t);
				++t;
			}
		return temp;
	}

	// update the world server every frame
	void Update(time_t diff);
	void CheckForExpiredInstances();

   
	void UpdateSessions(uint32 diff);

	WoWICE_INLINE void setRate(int index,float value)
	{
		regen_values[index]=value;
	}

	WoWICE_INLINE float getRate(int index)
	{
		return regen_values[index];
	}
	
	WoWICE_INLINE uint32 getIntRate(int index)
	{
		return int_rates[index];
	}

	WoWICE_INLINE void setIntRate(int index, uint32 value)
	{
		int_rates[index] = value;
	}

	// talent inspection lookup tables
	std::map< uint32, uint32 > InspectTalentTabPos;
	std::map< uint32, uint32 > InspectTalentTabSize;
	std::map< uint32, uint32 > InspectTalentTabBit;
	uint32 InspectTalentTabPages[12][3];

	// map text emote to spell prices
	typedef std::map< uint32, uint32> SpellPricesMap;
	SpellPricesMap mPrices;

	WoWICE_INLINE uint32 GetTimeOut(){return TimeOut;}

	struct NameGenData
	{
		string name;
		uint32 type;
	};
	vector<NameGenData> _namegendata[3];
	void LoadNameGenData();
	std::string GenerateName(uint32 type = 0);

	std::map<uint32, AreaTable*> mAreaIDToTable;
	std::map<uint32, AreaTable*> mZoneIDToTable;

	uint32 AddQueuedSocket(WorldSocket* Socket);
	void RemoveQueuedSocket(WorldSocket* Socket);
	uint32 GetQueuePos(WorldSocket* Socket);
	void UpdateQueuedSessions(uint32 diff);

	Mutex queueMutex;

	uint32 mQueueUpdateInterval;
	bool m_useIrc;

	void SaveAllPlayers();

	string MapPath;
	string vMapPath;
	bool UnloadMapFiles;
	bool BreathingEnabled;
	bool SpeedhackProtection;
	uint32 mInWorldPlayerCount;
	uint32 mAcceptedConnections;
	uint32 SocketSendBufSize;
	uint32 SocketRecvBufSize;

	int32 StartingLevel;
	uint32 ExtraTalents;
	uint32 MaxProfs;
	uint32 DKStartTalentPoints;

	uint32 PeakSessionCount;
	uint32 ArenaQueueDiff;
	bool SendStatsOnJoin;
	SessionSet gmList;
	bool Collision;
	bool DisableFearMovement;

	void ShutdownClasses();
	void DeleteObject(Object * obj);

	uint32 compression_threshold;

	void	SetKickAFKPlayerTime(uint32 idletimer){m_KickAFKPlayers=idletimer;}
	uint32	GetKickAFKPlayerTime(){return m_KickAFKPlayers;}

    uint32 GetRealmType() { return realmtype; }

	uint32 flood_lines;
	uint32 flood_seconds;
	bool flood_message;
	bool gm_skip_attunement;

	bool show_gm_in_who_list;
	uint32 map_unload_time;

	bool interfaction_chat;
	bool interfaction_group;
	bool interfaction_guild;
	bool interfaction_trade;
	bool interfaction_friend;
	bool interfaction_misc;
	bool crossover_chars;
	bool antiMasterLootNinja;
	bool gamemaster_listOnlyActiveGMs;
	bool gamemaster_hidePermissions;
	bool gamemaster_startonGMIsland;

	//Arena Settings
	int Arena_Season;
	int Arena_Progress;
	

	// broadcast system config
	bool BCSystemEnable;
	int BCInterval;
	int BCTriggerPercentCap;
	int BCOrderMode;

	bool realmAllowTBCcharacters;
	
	std::string announce_tag;
	bool GMAdminTag;
	bool NameinAnnounce;
	bool NameinWAnnounce;
	bool announce_output;

	int announce_tagcolor;
	int announce_gmtagcolor;
	int announce_namecolor;
	int announce_msgcolor;
	string ann_namecolor;
	string ann_gmtagcolor;
	string ann_tagcolor;
	string ann_msgcolor;
	void AnnounceColorChooser(int tagcolor, int gmtagcolor, int namecolor, int msgcolor);

	bool antihack_teleport;
	bool antihack_speed;
	bool antihack_flight;
	uint32 flyhack_threshold;
	bool no_antihack_on_gm;

	bool instance_TakeGroupLeaderID;
	bool instance_SlidingExpiration;
	int instance_DailyHeroicInstanceResetHour;
	bool instance_CheckTriggerPrerequsites;

	// battleground set
	uint32 m_bgSet_AV_MIN;
	uint32 m_bgSet_AV_MAX;
	uint32 m_bgSet_AB_MIN;
	uint32 m_bgSet_AB_MAX;
	uint32 m_bgSet_WS_MIN;
	uint32 m_bgSet_WS_MAX;
	uint32 m_bgSet_EOS_MIN;
	uint32 m_bgSet_EOS_MAX;
	uint32 m_bgSet_SOTA_MIN;
	uint32 m_bgSet_SOTA_MAX;

	// damage/hp/mp cap settings
	struct
	{
		bool enable;
		uint32 autoattackDamageCap;
		uint32 spellDamageCap;
		uint32 healthCap;
		uint32 manaCap;
		bool disconnect;
		bool broadcast;
	} m_limits;

	int GMTTimeZone;

	void CharacterEnumProc(QueryResultVector& results, uint32 AccountId);
	void LoadAccountDataProc(QueryResultVector& results, uint32 AccountId);

	void PollCharacterInsertQueue(DatabaseConnection * con);
	void PollMailboxInsertQueue(DatabaseConnection * con);
	void DisconnectUsersWithAccount(const char * account, WorldSession * session);
	void DisconnectUsersWithIP(const char * ip, WorldSession * session);
	void DisconnectUsersWithPlayerName(const char * plr, WorldSession * session);

	void LogoutPlayers();

protected:
	// update Stuff, FIX ME: use diff
	time_t _UpdateGameTime()
	{
		// Update Server time
		time_t thisTime = UNIXTIME;
		m_gameTime += thisTime - m_lastTick;
		m_lastTick = thisTime;

		return m_gameTime;
	}
	void FillSpellReplacementsTable();

private:
	EventableObjectHolder * eventholder;
	//! Timers
	typedef HM_NAMESPACE::hash_map<uint32, WorldSession*> SessionMap;
	SessionMap m_sessions;
	RWLock m_sessionlock;

	typedef HM_NAMESPACE::hash_map<uint32, AreaTrigger*> AreaTriggerMap;
	AreaTriggerMap m_AreaTrigger;

protected:
	Mutex SessionsMutex;//FOR GLOBAL !
	SessionSet Sessions;

	float regen_values[MAX_RATES];
	uint32 int_rates[MAX_INTRATES];

	uint32 m_playerLimit;
	bool m_allowMovement;
	bool m_gmTicketSystem;
	std::string m_motd;
   
    uint32 realmtype;

	time_t m_gameTime;
	time_t m_lastTick;
	uint32 TimeOut;

	uint32 m_StartTime;
	uint32 m_queueUpdateTimer;

	QueueSet mQueuedSessions;

	uint32	m_KickAFKPlayers;//don't lag the server if you are useless anyway :P
public:
	std::string GmClientChannel;
	bool m_reqGmForCommands;
	bool m_lfgForNonLfg;
	list<SpellEntry*> dummyspells;
	uint32 m_levelCap;
	uint32 m_genLevelCap;
	bool m_limitedNames;
	bool m_useAccountData;
	bool m_AdditionalFun;

	// Gold Cap
	bool GoldCapEnabled;
	uint32 GoldLimit;
	uint32 GoldStartAmount;

	bool m_LuaEngine;

	char * m_banTable;

	static float m_movementCompressThreshold;
	static float m_movementCompressThresholdCreatures;
	static uint32 m_movementCompressRate;
	static uint32 m_movementCompressInterval;
};

#define sWorld World::getSingleton()

#endif