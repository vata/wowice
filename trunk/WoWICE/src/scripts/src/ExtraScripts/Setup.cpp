#include "StdAfx.h"
#include "Setup.h"
#include <ScriptSetup.h>

extern "C" SCRIPT_DECL uint32 _exp_get_script_type()
{
	return SCRIPT_TYPE_MISC;
}

extern "C" SCRIPT_DECL void _exp_script_register(ScriptMgr* mgr)
{
	if(Config.OptionalConfig.GetBoolDefault("Extra", "Instant80", false))
	{
		sLog.outColor(TGREEN,"\n	Instant80 Enabled");
		SetupInstant80(mgr);
	}
/*
	if(Config.MainConfig.GetBoolDefault("Extra", "L80etc", false))
	{
		sLog.outColor(TGREEN,"\n	L80etc Enabled");
		SetupL80etc(mgr);
	}
*/
	if(Config.OptionalConfig.GetBoolDefault("Extra", "Portals", false))
	{
		sLog.outColor(TGREEN,"\n	Portals Enabled");
		SetupPortals(mgr);
	}
	/*if(Config.OptionalConfig.GetBoolDefault("Extra", "PVPToken", false))
	{
		sLog.outColor(TGREEN,"\n	PvP Tokens Enabled");
		SetupPvPToken(mgr);
	}*/
/*
	if(Config.OptionalConfig.GetBoolDefault("Extra", "WeddingNPC", false))
	{
		sLog.outColor(TGREEN,"\n	WeddingNPC Enabled");
		SetupWeddingNPC(mgr);
	}
*/

    // Allows users to type "+unstuck" without quotes to revive them if
	// needed and teleport them to either Stormwind or Orgrimmar
    if(Config.OptionalConfig.GetBoolDefault("Extra", "Unstuck", false))
    {
        sLog.outColor(TGREEN,"\n    Unstuck Enabled");
        SetupUnstuck(mgr);
    }

	sLog.outColor(TNORMAL, "\n");
}

#ifdef WIN32

BOOL APIENTRY DllMain( HANDLE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved )
{
	return TRUE;
}

#endif
