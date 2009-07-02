#include "StdAfx.h"
#include "Setup.h"

class PortalEffectSunwellIsle : public GameObjectAIScript
{
public:
  PortalEffectSunwellIsle(GameObject* goinstance) : GameObjectAIScript(goinstance) {}
  void OnActivate(Player * pPlayer)
  {
        if(pPlayer->getLevel() >= 70 && pPlayer->HasSpell(44934)) // optional you can check for quest 11513
        {
			pPlayer->SafeTeleport(530, 530, 13001.9f, -6907.46f, 9.56139f, 0.616532f);
        }
        else if(pPlayer->getLevel() <= 69)
        {
			pPlayer->BroadcastMessage("You must be level 70 to use this!");
        }
        else if(!pPlayer->HasSpell(44934))
        {
			pPlayer->BroadcastMessage("You must complete the quest first!");
        }
  }
  static GameObjectAIScript *Create(GameObject * GO) { return new PortalEffectSunwellIsle(GO); }
};
GameObjectAIScript * create_go(GameObject * GO) { return new PortalEffectSunwellIsle(GO); }
void SetupQDGoHandlers(ScriptMgr * mgr)
{
      mgr->register_gameobject_script(187056, &PortalEffectSunwellIsle::Create);  
}