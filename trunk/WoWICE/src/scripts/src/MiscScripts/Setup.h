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

#include "StdAfx.h"
#include "../Common/EasyFunctions.h"

#ifndef MISC_SCRIPTS_SETUP_H
#define MISC_SCRIPTS_SETUP_H

#define TO_CREATURE(ptr) static_cast<Creature*>(ptr) 
#define TO_PLAYER(ptr) static_cast<Player*>(ptr)
#define TO_OBJECT(ptr) static_cast<Object*>(ptr)
#define TO_UNIT(ptr) static_cast<Unit*>(ptr)
#define TO_PET(ptr) static_cast<Pet*>(ptr)
#define TO_ITEM(ptr) static_cast<Item*>(ptr)

void SetupGoHandlers(ScriptMgr * mgr);
void SetupQDGoHandlers(ScriptMgr * mgr);
void SetupRandomScripts(ScriptMgr * mgr);
void SetupMiscCreatures(ScriptMgr * mgr);
void SetupDarkmoonFaireObjects(ScriptMgr * mgr);
void InitializeGameObjectTeleportTable(ScriptMgr * mgr);

#endif
