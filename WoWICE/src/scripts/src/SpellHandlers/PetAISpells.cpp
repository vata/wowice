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
#include "Setup.h"

class DancingRuneWeaponAI : public CreatureAIScript
{
public:
	ADD_CREATURE_FACTORY_FUNCTION(DancingRuneWeaponAI);
	DancingRuneWeaponAI(Creature* pCreature) : CreatureAIScript(pCreature)
	{ 
		Player *pOwner = static_cast< Player* >(_unit->GetAIInterface()->GetPetOwner());
		
		if(pOwner)
		{
			Item * item = pOwner->GetItemInterface()->GetInventoryItem( EQUIPMENT_SLOT_MAINHAND );
			for( int s = 0; s < 5; s++)
			{
				if( item->GetProto()->Spells[s].Id == 0 )
					continue;
				if( item->GetProto()->Spells[s].Trigger == CHANCE_ON_HIT )
				{

					procSpell[s] = item->GetProto()->Spells[s].Id;	
				}
			}
		}
	}

	void OnDied(Unit *mKiller){ RemoveAIUpdateEvent(); }


	void OnCombatStart(Unit* mTarget) 
	{
		RegisterAIUpdateEvent(_unit->GetUInt32Value(UNIT_FIELD_BASEATTACKTIME));
		dpsCycle = 0;
	}
	
	void OnCombatStop(Unit* mTarget) 
	{
		RemoveAIUpdateEvent();
		dpsCycle = 0;
	}
	
	void AIUpdate() 
	{
	Unit *curtarget = _unit->GetAIInterface()->GetNextTarget();
		if(_unit->GetCurrentSpell() == NULL && curtarget)
		{
			switch(dpsCycle)
			{
			case 0:
			dpsSpell = 49921; // Plague Strike
			break;
			case 1:
			dpsSpell = 49909; // Icy Touch
			break;
			case 2:
			case 3:
			dpsSpell = 55262; // Heart Strike x 2
			break;
			case 4:
			dpsSpell = 51425; // Obliterate
			break;
			case 5:
			dpsSpell = 49895; // Death Coil
			break;
			case 6:
			case 7:
			dpsSpell = 51425; // Obliterate x 2
			break;
			case 8:
			case 9:
			dpsSpell = 55262; // Heart Strike x 2 
			break;
			case 10:
			case 11:
			dpsSpell = 49895; // Death Coil x 2
			break;
			}
		dpsCycle++;
		if(dpsCycle > 11)
			dpsCycle = 0;

		SpellEntry *MyNextSpell = dbcSpell.LookupEntryForced(dpsSpell);
		if(MyNextSpell != NULL)
			_unit->CastSpell(curtarget, MyNextSpell, true);

		}
	}

	void OnHit(Unit* mTarget, float fAmount)
	{
		for( int p = 0; p < 5; p++)
		{
			if(procSpell[p] != 0)
			{
			SpellEntry *mProc = dbcSpell.LookupEntryForced(procSpell[p]);
			if(!mProc)
				return;
			int x = rand()%100;
			uint32 proc = mProc->procChance;
			if(proc < 1)
				proc = 10; // Got to be fair :P

			if( (uint32)x <= proc )
				{
					Unit *Vic = mProc->self_cast_only ? _unit : mTarget;
					_unit->CastSpell(Vic,mProc,true);
				}
			}
		}
	}
private:
	int dpsCycle;
	int dpsSpell;
	int procSpell[5];
};

void SetupPetAISpells(ScriptMgr * mgr)
{
    mgr->register_creature_script(27893, &DancingRuneWeaponAI::Create);
};