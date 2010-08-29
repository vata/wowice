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

bool Penance(uint32 i, Spell * pSpell)
{
	if( !pSpell->p_caster || !pSpell->p_caster->isAlive() || 
		!pSpell->GetUnitTarget() || !pSpell->GetUnitTarget()->isAlive() )
		return true;

	Unit *target = pSpell->GetUnitTarget();
	Player *player = pSpell->p_caster;

	// index 0 contains the spell for the first tick, index 1 is the peroidic cast spell.
	uint32 hostileSpell[] = {0, 0};
	uint32 friendlySpell[] = {0, 0};

	switch( pSpell->GetProto()->Id )
	{
	case 47540: //Rank 1
		hostileSpell[0] = 47666;
		hostileSpell[1] = 47758;

		friendlySpell[0] = 47750;
		friendlySpell[1] = 47757;
		break;
	case 53005:
		hostileSpell[0] = 52998;
		hostileSpell[1] = 53001;

		friendlySpell[0] = 52983;
		friendlySpell[1] = 52986;
		break;
	case 53006:
		hostileSpell[0] = 52999;
		hostileSpell[1] = 53002;

		friendlySpell[0] = 52984;
		friendlySpell[1] = 52987;
		break;
	case 53007:
		hostileSpell[0] = 53000;
		hostileSpell[1] = 53003;

		friendlySpell[0] = 52985;
		friendlySpell[1] = 52988;
		break;
	}

	if( isAttackable(player, target) ) // Do holy damage
	{
		// First tick is instant.
		player->CastSpell(target, hostileSpell[0], true);
		player->CastSpell(target, hostileSpell[1], false);
	}
	else // Heal
	{ 
		player->CastSpell(target, friendlySpell[0], true);
		player->CastSpell(target, friendlySpell[1], false);
	}
	return true;
}

bool DivineAegis(uint32 i, Aura *pAura, bool apply)
{
	Unit *target = pAura->GetTarget();
	if( target == NULL )
		return true;

	if (apply)
		target->AddProcTriggerSpell(47753, pAura->GetSpellId(), pAura->m_casterGuid, pAura->GetSpellProto()->procChance, PROC_ON_SPELL_CRIT_HIT, 0, NULL, NULL);
	else
		target->RemoveProcTriggerSpell(47753, pAura->m_casterGuid);

	return true;
}

void SetupPriestSpells(ScriptMgr * mgr)
{
	uint32 PenanceIds[] =
	{
		47540, // Rank 1
		53005, // Rank 2
		53006, // Rank 3
		53007, // Rank 4
		0,
	};
    mgr->register_dummy_spell(PenanceIds, &Penance);

	uint32 DivineAegisIds[] = { 47509, 47511, 47515, 0 };
	mgr->register_dummy_aura(DivineAegisIds, &DivineAegis);
}
