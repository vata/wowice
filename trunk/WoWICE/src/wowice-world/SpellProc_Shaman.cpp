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

class FrostBrandAttackSpellProc : public SpellProc
{
	SPELL_PROC_FACTORY_FUNCTION(FrostBrandAttackSpellProc);

	void Init(Object *obj)
	{		
		mProcChance = TO_ITEM(obj)->GetProto()->Delay * 9 / 600;
	}
};

void SpellProcMgr::SetupShamman()
{
	AddByNameHash( SPELL_HASH_FROSTBRAND_ATTACK, &FrostBrandAttackSpellProc::Create );
}
