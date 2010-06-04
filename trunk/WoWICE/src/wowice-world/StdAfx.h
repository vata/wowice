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

#ifndef __STDAFX_H
#define __STDAFX_H

#ifdef min
#undef min
#endif

#ifdef max
#undef max
#endif

#define TO_CREATURE(ptr) static_cast<Creature*>(ptr) 
#define TO_PLAYER(ptr) static_cast<Player*>(ptr)
#define TO_OBJECT(ptr) static_cast<Object*>(ptr)
#define TO_UNIT(ptr) static_cast<Unit*>(ptr)
#define TO_PET(ptr) static_cast<Pet*>(ptr)


#include "Definitions.h"

#include <cstring>
#include <cstdlib>
#include <list>
#include <vector>
#include <map>
#include <sstream>
#include <string>

#include "../wowice-shared/Common.h"
#include "../wowice-shared/MersenneTwister.h"
#include "../wowice-shared/WorldPacket.h"
#include "../wowice-shared/Log.h"
#include "../wowice-shared/NGLog.h"
#include "../wowice-shared/ByteBuffer.h"
#include "../wowice-shared/StackBuffer.h"
#include "../wowice-shared/Config/ConfigEnv.h"
#include "../wowice-shared/crc32.h"
#include "../wowice-shared/LocationVector.h"

#include <zlib.h>

#include "../wowice-shared/Database/DatabaseEnv.h"
#include "../wowice-shared/Database/DBCStores.h"
#include "../wowice-shared/Database/dbcfile.h"

#include <Network/Network.h>

#include "../wowice-shared/Auth/MD5.h"
#include "../wowice-shared/Auth/BigNumber.h"
#include "../wowice-shared/Auth/Sha1.h"
#include "../wowice-shared/Auth/WowCrypt.h"
#include "../wowice-shared/FastQueue.h"
#include "../wowice-shared/CircularQueue.h"
#include "../wowice-shared/Threading/RWLock.h"
#include "../wowice-shared/Threading/Condition.h"
#include "../wowice-shared/Threading/Atomicity.h"
#include "../wowice-shared/wowice_getopt.h"

#ifdef WIN32
#include "printStackTrace.h"
#endif

#include "WUtil.h"
#include "UpdateFields.h"
#include "UpdateMask.h"
#include "Opcodes.h"
#include "AuthCodes.h"
#include "../wowice-shared/CallBack.h"
#include "WordFilter.h"
#include "EventMgr.h"
#include "EventableObject.h"
#include "Object.h"
#include "LootMgr.h"
#include "SpellProc.h"
#include "Unit.h"

#ifdef ENABLE_ACHIEVEMENTS
#include "AchievementMgr.h"
#endif

#include "AddonMgr.h"
#include "AIInterface.h"
#include "AreaTrigger.h"
#include "BattlegroundMgr.h"
#include "AlteracValley.h"
#include "ArathiBasin.h"
#include "EyeOfTheStorm.h"
#include "WorldState.h"
#include "CellHandler.h"
#include "Chat.h"
#include "Corpse.h"
#include "Quest.h"
#include "QuestMgr.h"
#include "Creature.h"
#include "DynamicObject.h"
#include "GameObject.h"
#include "Group.h"
#include "Guild.h"
#include "HonorHandler.h"
#include "ItemPrototype.h"
#include "Item.h"
#include "Container.h"
#include "AuctionHouse.h"
#include "AuctionMgr.h"
#include "LfgMgr.h"
#include "MailSystem.h"
#include "Map.h"
#include "MapCell.h"
#include "TerrainMgr.h"
#include "MiscHandler.h"
#include "NameTables.h"
#include "NPCHandler.h"
#include "Pet.h"
#include "WorldSocket.h"
#include "WorldSession.h"
#include "MapMgr.h"
#include "MapScriptInterface.h"
#include "Player.h"
#include "faction.h"
#include "Skill.h"
#include "SkillNameMgr.h"
#include "SpellNameHashes.h"
#include "Spell.h"
#include "SpellAuras.h"
#include "TaxiMgr.h"
#include "TransporterHandler.h"
#include "StrandOfTheAncient.h"
#include "WarsongGulch.h"
#include "WeatherMgr.h"
#include "World.h"
#include "ItemInterface.h"
#include "Stats.h"
#include "WorldCreator.h"
#include "ObjectContainer.h"
#include "Vehicle.h"
#include "ObjectMgr.h"
#include "CThreads.h"
#include "ScriptMgr.h"
#include "Channel.h"
#include "ChannelMgr.h"
#include "ArenaTeam.h"
#include "Arenas.h"
#include "LogonCommClient.h"
#include "LogonCommHandler.h"
#include "MainServerDefines.h"
#include "WorldRunnable.h"
#include "../wowice-shared/Storage.h"
#include "ObjectStorage.h"
#include "DatabaseCleaner.h"
#include "DayWatcherThread.h"
#include "CommonScheduleThread.h"
#include "LocalizationMgr.h"
#include "CollideInterface.h"
#include "Master.h"
#include "BaseConsole.h"
#include "CConsole.h"
#include "SpeedDetector.h"
#include "ProcCondHandler.h"
#include "WorldStates.h"
#endif

#define RECRUITING "Info: |cff00FF7FWoWICE is recruiting developers."
#define BUGTRACKER "http://code.google.com/p/wowice/"

#ifndef WIN32
#include "UnixMetric.h"
#endif
