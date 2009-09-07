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

bool SymbolOfLife(uint32 i, Spell* pSpell) // Alliance res. quests
{
   // What is i for note the loops below just overwrote it with an int
   // starting at 0 so it doesnt do anything.

  if(!pSpell->u_caster->IsPlayer())
    return true;

  Player *plr = (Player*)pSpell->u_caster;
  Creature *target = plr->GetMapMgr()->GetCreature((uint32)plr->GetSelection());
  
  if(target == NULL)
    return true;

  const uint32 targets[] = {17542, 6177, 6172}; 
  const uint32 quests[] =  {9600,  1783, 1786};
  bool questOk = false;
  bool targetOk = false;

  for(int j = 0; j < 3; ++j)
  {
    if(target->GetEntry() == targets[j])
    {
      targetOk = true;
      
      break;
    }
  }
  
  if(!targetOk)
    return true;
  
  QuestLogEntry *qle;
  
  for(int j = 0; j < 3; ++j)
  {
    if(plr->GetQuestLogForEntry(quests[j]) != NULL)
    {
      qle = plr->GetQuestLogForEntry(quests[j]);
      questOk = true;
      
      break;
    }
  }
  
  if(!questOk)
    return true;

  target->SetStandState(0);
  target->setDeathState(ALIVE);

  target->Despawn(10*1000, 1*60*1000);

  qle->SetMobCount(0, 1);
  qle->SendUpdateAddKill(0);
  qle->UpdatePlayerFields();
  
  return true;
}

bool FilledShimmeringVessel(uint32 i, Spell* pSpell) // Blood Elf ress. quest
{
  if(!pSpell->u_caster->IsPlayer())
    return true;

  Player *plr = (Player*)pSpell->u_caster;
  
  Creature *target = plr->GetMapMgr()->GetCreature((uint32)plr->GetSelection());
  if(target == NULL)
    return true;

  if(target->GetEntry() != 17768)
    return true;

  QuestLogEntry *qle = plr->GetQuestLogForEntry(9685);
  if(qle == NULL)
    return true;

  target->SetStandState(0);
  target->setDeathState(ALIVE);

  target->Despawn(30*1000, 1*60*1000);

  qle->SetMobCount(0, 1);
  qle->SendUpdateAddKill(0);
  qle->UpdatePlayerFields();

  return true;
}

class PaladinDeadNPC : public CreatureAIScript
{
public:
  ADD_CREATURE_FACTORY_FUNCTION(PaladinDeadNPC);
  PaladinDeadNPC(Creature* pCreature) : CreatureAIScript(pCreature) {}

  void OnLoad()
  {
    _unit->SetStandState(7);
    _unit->setDeathState(CORPSE);
    _unit->GetAIInterface()->m_canMove = false;
  }
};

/*--------------------------------------------------------------------------------------------------------*/

class GildedBrazier : public GameObjectAIScript
{
public:
	GildedBrazier(GameObject* goinstance) : GameObjectAIScript(goinstance) {}
	static GameObjectAIScript *Create(GameObject * GO) { return new GildedBrazier(GO); }

	void OnActivate(Player * pPlayer)	
	{
		if(pPlayer->GetQuestLogForEntry(9678))
		{
			float SSX = pPlayer->GetPositionX();
			float SSY = pPlayer->GetPositionY();
			float SSZ = pPlayer->GetPositionZ();
			float SSO = pPlayer->GetOrientation();
			
			GameObject* Brazier = pPlayer->GetMapMgr()->GetInterface()->GetGameObjectNearestCoords( SSX, SSY, SSZ, 181956);
			if (Brazier)
			{
				Brazier->SetUInt32Value( GAMEOBJECT_BYTES_1, 0);
				pPlayer->GetMapMgr()->GetInterface()->SpawnCreature(17716, SSX, SSY, SSZ, SSO, true, false, 0, 0)->Despawn(600000, 0);
			}
		}
		else
		{
			pPlayer->BroadcastMessage("Missing required quest : The First Trial");
		}
	}
};

class stillbladeQAI : public CreatureAIScript
{
public:
	ADD_CREATURE_FACTORY_FUNCTION(stillbladeQAI);
    	stillbladeQAI(Creature* pCreature) : CreatureAIScript(pCreature)  
    	{
    	
	}
	
	void OnDied(Unit *mKiller) 
	{
		float SSX = mKiller->GetPositionX();
		float SSY = mKiller->GetPositionY();
		float SSZ = mKiller->GetPositionZ();
		float SSO = mKiller->GetOrientation();
			
		GameObject* Brazier = mKiller->GetMapMgr()->GetInterface()->GetGameObjectNearestCoords( SSX, SSY, SSZ, 181956);
		if (Brazier)
		{
			Brazier->SetUInt32Value( GAMEOBJECT_BYTES_1, 1);
		}
	}
};


void SetupPaladin(ScriptMgr * mgr)
{
  mgr->register_dummy_spell(8593, &SymbolOfLife);
  mgr->register_dummy_spell(31225, &FilledShimmeringVessel);
  mgr->register_creature_script(17768, &PaladinDeadNPC::Create);
  mgr->register_creature_script(17542, &PaladinDeadNPC::Create);
  mgr->register_creature_script(6177, &PaladinDeadNPC::Create);
  mgr->register_creature_script(6172, &PaladinDeadNPC::Create);
  mgr->register_gameobject_script(181956, &GildedBrazier::Create);
  mgr->register_creature_script(17716, &stillbladeQAI::Create);
}