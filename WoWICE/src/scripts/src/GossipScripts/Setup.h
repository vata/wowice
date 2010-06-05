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

#ifndef GOSSIP_SCRIPTS_SETUP_H
#define GOSSIP_SCRIPTS_SETUP_H

#define TO_CREATURE(ptr) static_cast<Creature*>(ptr) 
#define TO_PLAYER(ptr) static_cast<Player*>(ptr)
#define TO_OBJECT(ptr) static_cast<Object*>(ptr)
#define TO_UNIT(ptr) static_cast<Unit*>(ptr)
#define TO_PET(ptr) static_cast<Pet*>(ptr)
#define TO_ITEM(ptr) static_cast<Item*>(ptr)

void SetupInnkeepers(ScriptMgr * mgr);
void SetupGuardGossip(ScriptMgr * mgr);
void SetupTrainerScript(ScriptMgr * mgr);
void SetupMulgoreGossip(ScriptMgr * mgr);
void SetupShattrathGossip(ScriptMgr * mgr);
void SetupTanarisGossip(ScriptMgr * mgr);
void SetupMoongladeGossip(ScriptMgr * mgr);
void SetupStormwindGossip(ScriptMgr * mgr);
void SetupTheramoreGossip(ScriptMgr * mgr);
void SetupDarkmoonFaireGossip(ScriptMgr * mgr);
void SetupDarkmoonFaireBarker(ScriptMgr * mgr);
void SetupTeldrassilGossip(ScriptMgr * mgr);
void SetupBoreanTundraGossip(ScriptMgr * mgr);
void SetupWyrmrestTempleGossip(ScriptMgr * mgr);
void SetupXpEliminatorGossip(ScriptMgr *mgr);

#endif
