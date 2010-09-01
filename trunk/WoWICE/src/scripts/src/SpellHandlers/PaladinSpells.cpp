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

bool EyeForAnEye(uint32 i, Aura *pAura, bool apply)
{
	Unit *target = pAura->GetTarget();

	if (apply)
		target->AddProcTriggerSpell(25997, pAura->GetSpellProto()->Id, pAura->m_casterGuid, pAura->GetSpellProto()->procChance, PROC_ON_CRIT_HIT_VICTIM | PROC_ON_RANGED_CRIT_ATTACK_VICTIM | PROC_ON_SPELL_CRIT_HIT_VICTIM, 0, NULL, NULL);
	else
		target->RemoveProcTriggerSpell(25997, pAura->m_casterGuid);

	return true;
}

bool HolyShock(uint32 i, Spell * pSpell) 
{
	Unit* target = pSpell->GetUnitTarget();
	if( target == NULL )
		return true;

	Player* caster = pSpell->p_caster;
	if( caster == NULL )
		return true; 

	uint32 spell_id = 0;

	if( isFriendly(caster, target) )
		switch( pSpell->GetProto()->Id )
		{
			case 20473: spell_id = 25914; break;
			case 20929: spell_id = 25913; break;
			case 20930: spell_id = 25903; break;
			case 27174: spell_id = 27175; break;
			case 33072: spell_id = 33074; break;
			case 48824: spell_id = 48820; break;
			case 48825: spell_id = 48821; break;
		}
	else
		switch( pSpell->GetProto()->Id )
		{
			case 20473: spell_id = 25912; break;
			case 20929: spell_id = 25911; break;
			case 20930: spell_id = 25902; break;
			case 27174: spell_id = 27176; break;
			case 33072: spell_id = 33073; break;
			case 48824: spell_id = 48822; break;
			case 48825: spell_id = 48823; break;
		}

	if( spell_id )
		caster->CastSpell(target, spell_id, false);

	return true;  
}

bool SealOfRighteousness(uint32 i, Aura *pAura, bool apply)
{
	Unit *target = pAura->GetTarget();

	if( i == 0 )
	{
		if (apply)
			target->AddProcTriggerSpell(25742, pAura->GetSpellId(), pAura->m_casterGuid, pAura->GetSpellProto()->procChance, PROC_ON_MELEE_ATTACK, 0, NULL, NULL);
		else
			target->RemoveProcTriggerSpell(25742, pAura->m_casterGuid);
	}

	return true;
}

bool SealOfCorruption(uint32 i, Aura *pAura, bool apply)
{
	Unit *target = pAura->GetTarget();

	if( i == 0 )
	{
		if (apply)
		{
			target->AddProcTriggerSpell(53742, pAura->GetSpellId(), pAura->m_casterGuid, pAura->GetSpellProto()->procChance, PROC_ON_MELEE_ATTACK, 0, NULL, NULL);
			target->AddProcTriggerSpell(53739, pAura->GetSpellId(), pAura->m_casterGuid, pAura->GetSpellProto()->procChance, PROC_ON_MELEE_ATTACK, 0, NULL, NULL);
		}
		else
		{
			target->RemoveProcTriggerSpell(53742, pAura->m_casterGuid);
			target->RemoveProcTriggerSpell(53739, pAura->m_casterGuid);
		}
	}

	return true;
}

bool SealOfVengeance(uint32 i, Aura *pAura, bool apply)
{
	Unit *target = pAura->GetTarget();

	if( i == 0 )
	{
		if (apply)
		{
			target->AddProcTriggerSpell(31803, pAura->GetSpellId(), pAura->m_casterGuid, pAura->GetSpellProto()->procChance, PROC_ON_MELEE_ATTACK, 0, NULL, NULL);
			target->AddProcTriggerSpell(42463, pAura->GetSpellId(), pAura->m_casterGuid, pAura->GetSpellProto()->procChance, PROC_ON_MELEE_ATTACK, 0, NULL, NULL);
		}
		else
		{
			target->RemoveProcTriggerSpell(31803, pAura->m_casterGuid);
			target->RemoveProcTriggerSpell(42463, pAura->m_casterGuid);
		}
	}

	return true;
}

bool JudgementLightWisdomJustice(uint32 i, Spell * pSpell) 
{
	Unit* target = pSpell->GetUnitTarget();
	if( target == NULL )
		return true;

	Player* caster = pSpell->p_caster;
	if( caster == NULL )
		return true;

	// Search for a previous judgement casted by this caster. He can have only 1 judgement active at a time
	uint32 index = 0;
	uint32 judgements[] = { SPELL_HASH_JUDGEMENT_OF_LIGHT, SPELL_HASH_JUDGEMENT_OF_WISDOM, SPELL_HASH_JUDGEMENT_OF_JUSTICE,
							SPELL_HASH_JUDGEMENT_OF_VENGEANCE, SPELL_HASH_JUDGEMENT_OF_CORRUPTION, SPELL_HASH_JUDGEMENT_OF_RIGHTEOUSNESS, 0 };

	uint64 prev_target = caster->GetCurrentUnitForSingleTargetAura(judgements, &index);
	if( prev_target )
	{
		Unit *t = caster->GetMapMgr()->GetUnit(prev_target);

		if( t != NULL )
			t->RemoveAllAuraByNameHash(judgements[index]);

		caster->RemoveCurrentUnitForSingleTargetAura(judgements[index]);
	}

	// Search for seal to unleash its energy
	uint32 seals[] = { 20375, 20165, 20164, 21084, 31801, 53736, 20166, 0 };

	Aura *aura = caster->FindAura(seals);
	if( aura == NULL )
		return true;

	uint32 id = 0;
	switch( aura->GetSpellId() )
	{
		case 20375: id = 20467; break;
		case 20165: id = 54158; break;
		case 20164: id = 54158; break;
		case 21084: id = 20187; break;
		case 31801: id = aura->GetSpellProto()->EffectBasePoints[2]; break;
		case 53736: id = aura->GetSpellProto()->EffectBasePoints[2]; break;
		case 20166: id = 54158; break;
	}

	caster->CastSpell(target, id, true);

	// Cast judgement spell
	switch( pSpell->GetProto()->NameHash )
	{
		case SPELL_HASH_JUDGEMENT_OF_JUSTICE: id = 20184; break;
		case SPELL_HASH_JUDGEMENT_OF_LIGHT:   id = 20185; break;
		case SPELL_HASH_JUDGEMENT_OF_WISDOM:  id = 20186; break;
	}

	caster->CastSpell(target, id, true);

	caster->SetCurrentUnitForSingleTargetAura( pSpell->GetProto(), target->GetGUID() );

	return true;
}

bool JudgementOfLight(uint32 i, Aura *pAura, bool apply)
{
	Unit *caster = pAura->GetUnitCaster();
	if( caster == NULL )
		return true;

	if (apply)
		caster->AddProcTriggerSpell(20267, pAura->GetSpellId(), pAura->m_casterGuid, pAura->GetSpellProto()->procChance, PROC_ON_MELEE_ATTACK | PROC_TARGET_SELF, 0, NULL, NULL);
	else
		caster->RemoveProcTriggerSpell(20267, pAura->m_casterGuid);

	return true;	
}

bool JudgementOfWisdom(uint32 i, Aura *pAura, bool apply)
{
	Unit *caster = pAura->GetUnitCaster();
	if( caster == NULL )
		return true;

	if (apply)
		caster->AddProcTriggerSpell(20268, pAura->GetSpellId(), pAura->m_casterGuid, pAura->GetSpellProto()->procChance, PROC_ON_MELEE_ATTACK | PROC_TARGET_SELF, 0, NULL, NULL);
	else
		caster->RemoveProcTriggerSpell(20268, pAura->m_casterGuid);

	return true;	
}

void SetupPaladinSpells(ScriptMgr * mgr)
{
	mgr->register_dummy_aura(9799, &EyeForAnEye);
	mgr->register_dummy_aura(25988, &EyeForAnEye);

	uint32 HolyShockIds[] = { 20473, 20929, 20930, 27174, 33072, 48824, 48825, 0 };
	mgr->register_dummy_spell(HolyShockIds, &HolyShock);

	mgr->register_dummy_aura(21084, &SealOfRighteousness);
	mgr->register_dummy_aura(53736, &SealOfCorruption);
	mgr->register_dummy_aura(31801, &SealOfVengeance);

	mgr->register_dummy_spell(20271, &JudgementLightWisdomJustice);
	mgr->register_dummy_spell(53408, &JudgementLightWisdomJustice);
	mgr->register_dummy_spell(53407, &JudgementLightWisdomJustice);

	mgr->register_dummy_aura(20185, &JudgementOfLight);
	mgr->register_dummy_aura(20186, &JudgementOfWisdom);
}
