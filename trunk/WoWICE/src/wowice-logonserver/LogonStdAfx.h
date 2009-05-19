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

#pragma once

#include <list>
#include <vector>
#include <map>
#include <sstream>
#include <string>
//#include <fstream>

#include "Common.h"
#include <Network/Network.h>

#include "../wowice-shared/Log.h"
#include "../wowice-shared/Util.h"
#include "../wowice-shared/ByteBuffer.h"
#include "../wowice-shared/Config/ConfigEnv.h"
#include <zlib.h>

#include "../wowice-shared/Database/DatabaseEnv.h"
#include "../wowice-shared/Database/DBCStores.h"
#include "../wowice-shared/Database/dbcfile.h"

#include "../wowice-shared/Auth/BigNumber.h"
#include "../wowice-shared/Auth/Sha1.h"
#include "../wowice-shared/Auth/WowCrypt.h"
#include "../wowice-shared/CrashHandler.h"

#include "LogonOpcodes.h"
#include "../wowice-logonserver/Main.h"
#include "../wowice-world/NameTables.h"
#include "AccountCache.h"
#include "PeriodicFunctionCall_Thread.h"
#include "../wowice-logonserver/AutoPatcher.h"
#include "../wowice-logonserver/AuthSocket.h"
#include "../wowice-logonserver/AuthStructs.h"
//#include "../wowice-logonserver/LogonOpcodes.h"
#include "../wowice-logonserver/LogonCommServer.h"
#include "../wowice-logonserver/LogonConsole.h"
#include "../wowice-shared/WorldPacket.h"

// database decl
extern Database* sLogonSQL;
