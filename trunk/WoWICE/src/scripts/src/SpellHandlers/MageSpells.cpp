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

#include "Setup.h"

bool Cold_Snap(uint32 i, Spell * pSpell)
{
    if(!pSpell->p_caster) return true;
    pSpell->p_caster->ClearCooldownsOnLine(6, pSpell->GetProto()->Id);
    return true;
}

bool Deep_Freeze(uint32 i, Spell *pSpell)
{
	Unit *pTarget = pSpell->GetUnitTarget();
	if(!pSpell->p_caster || !pTarget) return true;
	if(!pTarget->HasFlag(UNIT_FIELD_AURASTATE, AURASTATE_FLAG_FROZEN)){
		// TODO: why isn't client updated with frozen state information
		// when mobs on serverside clearly has this info.
		// pTarget->SendChatMessage(CHAT_MSG_MONSTER_SAY, LANG_UNIVERSAL, "lol I r frozen");
		return true;
	}
	return true;
}

bool Living_Bomb(uint32 i, Aura *pAura, bool apply)
{
		Unit *caster = pAura->GetUnitCaster();
		if( caster && !apply )
			caster->CastSpell( pAura->GetTarget(), pAura->GetSpellProto()->EffectBasePoints[i]+1, true );
		return true;
}

void SetupMageSpells(ScriptMgr * mgr)
{
    mgr->register_dummy_spell(11958, &Cold_Snap);
	mgr->register_dummy_spell(44572, &Deep_Freeze);
	mgr->register_dummy_aura(55360, &Living_Bomb);
}
