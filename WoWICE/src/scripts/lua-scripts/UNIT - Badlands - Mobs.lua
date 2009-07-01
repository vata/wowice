--[[

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
 
-- ]]

-- http://www.wowhead.com/?zone=3
-- Total Units Complete = 9/90
function AmbassadorInfernus_OnEnterCombat(pUnit,Event)
	pUnit:RegisterEvent("AmbassadorInfernus_FireNova", 16000, 0)
	pUnit:RegisterEvent("AmbassadorInfernus_FireShieldIV", 24000, 0)
	pUnit:RegisterEvent("AmbassadorInfernus_SearingFlames", 13000, 0)
end

function AmbassadorInfernus_FireNova(pUnit,Event)
	pUnit:CastSpell(11970)
end

function AmbassadorInfernus_FireShieldIV(pUnit,Event)
	pUnit:CastSpell(2602)
end

function AmbassadorInfernus_SearingFlames(pUnit,Event)
	local searingCheck = pUnit:GetClosestPlayer()
	if (searingCheck ~= nil) then
	else
		pUnit:FullCastSpellOnTarget(9552,pUnit:GetClosestPlayer())
	end
end

function AmbassadorInfernus_OnLeaveCombat(pUnit,Event)
	pUnit:RemoveEvents()
end

function AmbassadorInfernus_OnDied(pUnit,Event)
	pUnit:RemoveEvents()
end

RegisterUnitEvent(2745, 1, "AmbassadorInfernus_OnEnterCombat")
RegisterUnitEvent(2745, 2, "AmbassadorInfernus_OnLeaveCombat")
RegisterUnitEvent(2745, 4, "AmbassadorInfernus_OnDied")

function Blacklash_OnEnterCombat(pUnit,Event)
	pUnit:RegsiterEvent("Blacklash_FlameBreath", 4500, 0)
end

function Blacklash_FlameBreath(pUnit,Event)
	pUnit:FullCastSpellOnTarget(9573,pUnit:GetClosestPlayer())
end

function Blacklash_OnLeaveCombat(pUnit,Event)
	pUnit:RemoveEvents()
end

function Blacklash_OnDied(pUnit,Event)
	pUnit:RemoveEvents()
end

RegisterUnitEvent(2757, 1, "Blacklash_OnEnterCombat")
RegisterUnitEvent(2757, 2, "Blacklash_OnLeaveCombat")
RegisterUnitEvent(2757, 4, "Blacklash_OnDied")

function Buzzard_OnEnterCombat(pUnit,Event)
	pUnit:RegisterEvent("Buzzard_InfectedWound", 38000, 0)
end

function Buzzard_InfectedWound(pUnit,Event)
	pUnit:FullCastSpellOnTarget(3427,pUnit:GetClosestPlayer())
end

function Buzzard_OnLeaveCombat(pUnit,Event)
	pUnit:RemoveEvents()
end

function Buzzard_OnDied(pUnit,Event)
	pUnit:RemoveEvents()
end

RegisterUnitEvent(2830, 1, "Buzzard_OnEnterCombat")
RegisterUnitEvent(2830, 2, "Buzzard_OnLeaveCombat")
RegisterUnitEvent(2830, 4, "Buzzard_OnDied")