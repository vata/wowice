#include "StdAfx.h"
#include "Setup.h"

bool Cold_Snap(uint32 i, Spell * pSpell)
{
    if(!pSpell->p_caster) return true;
    pSpell->p_caster->ClearCooldownsOnLine(6, pSpell->GetProto()->Id);
    return true;
}

bool Deep_Freeze(uint32 i, Spell *pSpell){
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

bool Fiery_Payback(uint32 i, Spell *pSpell){
	
	if(!pSpell->p_caster) return true;
	if(!pSpell->p_caster->HasFlag(UNIT_FIELD_AURASTATE, AURASTATE_FLAG_HEALTH35))
		pSpell->m_spellInfo->Effect[0] = pSpell->m_spellInfo->Effect[1] = pSpell->m_spellInfo->Effect[2] = 0;
	return true;
}

bool Living_Bomb(uint32 i, Aura *pAura, bool apply){
	// TODO: find an effective way to use a timer
	// might borrow the one in cooldown mapping
	return false;
}

void SetupMageSpells(ScriptMgr * mgr)
{
    mgr->register_dummy_spell(11958, &Cold_Snap);
	mgr->register_dummy_spell(44572, &Deep_Freeze);
	mgr->register_dummy_aura(55360, &Living_Bomb);
	mgr->register_dummy_spell(44440, &Fiery_Payback);
	mgr->register_dummy_spell(44441, &Fiery_Payback);
}
