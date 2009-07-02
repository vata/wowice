#include "StdAfx.h"
#include "Setup.h"


//Corrupt Minor Manifestation Water Dead
class Corrupt_Minor_Manifestation_Water_Dead : public CreatureAIScript
{
public:
  ADD_CREATURE_FACTORY_FUNCTION(Corrupt_Minor_Manifestation_Water_Dead);
  Corrupt_Minor_Manifestation_Water_Dead(Creature* pCreature) : CreatureAIScript(pCreature) {}

  void OnDied(Unit *mKiller)
  {
    float SSX = _unit->GetPositionX();
    float SSY = _unit->GetPositionY();
    float SSZ = _unit->GetPositionZ();
    float SSO = _unit->GetOrientation();

    _unit->GetMapMgr()->GetInterface()->SpawnCreature(5895, SSX, SSY+1, SSZ, SSO, true, false, 0, 0)->Despawn(600000, 0);
  }
};

class SavannahProwler : public CreatureAIScript
{
public:
  SavannahProwler(Creature* pCreature) : CreatureAIScript(pCreature) {}

  void OnLoad()
  {
    uint8 chance = RandomUInt(3);

    if(chance == 1)
      _unit->SetStandState(STANDSTATE_SLEEP); 
  }

  void OnCombatStart()
  {
    if(_unit->GetStandState() == STANDSTATE_SLEEP)
      _unit->SetStandState(0);
  }


  static CreatureAIScript *Create(Creature * c) { return new SavannahProwler(c); }
};

//Lazy Peons
class PeonSleepingAI : public CreatureAIScript
{
public:
	ADD_CREATURE_FACTORY_FUNCTION(PeonSleepingAI);
	PeonSleepingAI(Creature* pCreature) : CreatureAIScript(pCreature) 
	{
		Unit * target = static_cast< Unit* >(_unit);
		SpellEntry * pSpellEntry = dbcSpell.LookupEntry(18795);
		sEventMgr.AddEvent( target ,&Unit::EventCastSpell , target , pSpellEntry , 0, 3000 + RandomUInt( 180000 ), 1, 1 );
	}
};

void SetupMiscCreatures(ScriptMgr *mgr)
{
	mgr->register_creature_script(5894, &Corrupt_Minor_Manifestation_Water_Dead::Create);
	mgr->register_creature_script(3425, &SavannahProwler::Create);
	mgr->register_creature_script(10556, &PeonSleepingAI::Create);
}
