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
#define SKIP_ALLOCATOR_SHARING 1
#include <ScriptSetup.h>

extern "C" SCRIPT_DECL uint32 _exp_get_script_type()
{
	return SCRIPT_TYPE_MISC;
}

extern "C" SCRIPT_DECL void _exp_script_register(ScriptMgr* mgr)
{
	SetupDruid(mgr);
	SetupPaladin(mgr);
	SetupShadowArcScript(mgr);
	SetupHellfirePeninsula(mgr);
	SetupBladeEdgeMountains(mgr);
	SetupTerrokarForest(mgr);
	SetupNagrand(mgr);
	SetupSilverpineForest(mgr);
	SetupZangarmarsh(mgr);
	SetupUndercity(mgr);
	SetupAzuremystIsle(mgr);
	SetupUnGoro(mgr);
	SetupMage(mgr);
	SetupBarrens(mgr);
	SetupIsleOfQuelDanas(mgr);
	SetupGhostlands(mgr);
	SetupEversongWoods(mgr);
	SetupThousandNeedles(mgr);
	SetupOrgrimmar(mgr);
}

#ifdef WIN32

BOOL APIENTRY DllMain( HANDLE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved )
{
    return TRUE;
}

#endif
