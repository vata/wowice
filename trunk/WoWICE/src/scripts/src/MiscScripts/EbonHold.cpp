#include "StdAfx.h"
#include "Setup.h"

/*************Teleporters Begin**************/
// Notes: Please try to keep this file clean if modifications are made.
// Also, please include references to header files, and locations for easy access, thanks.
// Lower level of Ebon Hold Teleporter / Teleport up

class SCRIPT_DECL Doodad_Nox_portal_purple_bossroom01 : public GameObjectAIScript
 {
public:
	static GameObjectAIScript *Create(GameObject * GO) { return new Doodad_Nox_portal_purple_bossroom01(GO); }
    Doodad_Nox_portal_purple_bossroom01 (GameObject* goinstance) : GameObjectAIScript(goinstance)
     {
	    RegisterAIUpdateEvent(1);
	 }
     void AIUpdate()
	 {
         set<Player*>::iterator itr = _gameobject->GetInRangePlayerSetBegin();
         for(; itr != _gameobject->GetInRangePlayerSetEnd(); ++itr)
         {
		 Player * Plr = (*itr);
			if( _gameobject->CalcDistance( _gameobject, Plr ) <= 2.0f )
			{
			   Plr->SafeTeleport( Plr->GetMapId(), Plr->GetInstanceID(), 2422.375977f, -5619.545410f, 420.643860f, 3.730638f);
			}
         }
     }
};

// Upper level of Ebon Hold Teleporter / Teleports down

class SCRIPT_DECL Doodad_Nox_portal_purple_bossroom17 : public GameObjectAIScript
 {
public:
	static GameObjectAIScript *Create(GameObject * GO) { return new Doodad_Nox_portal_purple_bossroom17(GO); }
    Doodad_Nox_portal_purple_bossroom17 (GameObject* goinstance) : GameObjectAIScript(goinstance)
     {
	    RegisterAIUpdateEvent(1);
	 }
     void AIUpdate()
	 {
         set<Player*>::iterator itr = _gameobject->GetInRangePlayerSetBegin();
         for(; itr != _gameobject->GetInRangePlayerSetEnd(); ++itr)
         {
		 Player * Plr = (*itr);
			if( _gameobject->CalcDistance( _gameobject, Plr ) <= 2.0f )
			{
			   Plr->SafeTeleport( Plr->GetMapId(), Plr->GetInstanceID(), 2402.206299f, -5632.441895f, 377.021484f, 3.725146f);
			}
         }
     }
};
/*************Teleporters End**************/


/*********************************************
// Scourge Gryphon Taxi Start
**********************************************/

class ScourgeGryphonDown : public GossipScript //Acherus -> Death's Breach
{
public:
	void GossipHello(Object * pObject, Player* Plr, bool AutoSend)
	{
	TaxiPath * taxipath = sTaxiMgr.GetTaxiPath(1053);
	Plr->DismissActivePet();
	Plr->TaxiStart(taxipath, 26308, 0);
	}
};

class ScourgeGryphonUp : public GossipScript //Death's Breach -> Acherus
{
public:
	void GossipHello(Object * pObject, Player* Plr, bool AutoSend)
	{
	TaxiPath * taxipath = sTaxiMgr.GetTaxiPath(1054);
	Plr->DismissActivePet();
	Plr->TaxiStart(taxipath, 26308, 0);
	}
};

/*********************************************
// Scourge Gryphon Taxi End
**********************************************/

void SetupEbonHold(ScriptMgr * mgr)
{
	mgr->register_gameobject_script(191538, &Doodad_Nox_portal_purple_bossroom01::Create);
	mgr->register_gameobject_script(191539, &Doodad_Nox_portal_purple_bossroom17::Create);
	GossipScript * SGDOWN = (GossipScript*) new ScourgeGryphonDown();
	mgr->register_gossip_script(29488, SGDOWN);
	GossipScript * SGUP = (GossipScript*) new ScourgeGryphonUp();
	mgr->register_gossip_script(29501, SGUP);
}