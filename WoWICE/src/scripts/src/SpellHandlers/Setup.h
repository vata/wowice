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

#ifndef SPELL_SCRIPTS_SETUP_H
#define SPELL_SCRIPTS_SETUP_H

#ifdef WIN32
#pragma warning(disable:4244)
#endif

void SetupShamanSpells(ScriptMgr * mgr);
void SetupWarlockSpells(ScriptMgr * mgr);
void SetupWarriorSpells(ScriptMgr * mgr);
void SetupHunterSpells(ScriptMgr * mgr);
void SetupItemSpells_1(ScriptMgr * mgr);
void SetupOldSpellCPPSuff(ScriptMgr * mgr);
void SetupMageSpells(ScriptMgr * mgr);
void SetupPaladinSpells(ScriptMgr * mgr);
void SetupRogueSpells(ScriptMgr * mgr);
void SetupPriestSpells(ScriptMgr * mgr);
void SetupPetAISpells(ScriptMgr * mgr);
void SetupQuestItems(ScriptMgr * mgr);
void SetupDruidSpells(ScriptMgr * mgr);
void SetupDeathKnightSpells(ScriptMgr * mgr);

//Instance spells (mainly scripted targets)
void SetupRaidBlackTempleSpells(ScriptMgr* mgr);

#endif
