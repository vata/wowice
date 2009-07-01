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

-- Scripted By:  n4xD

function Dragonflayer_Weaponsmith_OnCombat(pUnit, Event)
pUnit:RegisterEvent("Dragonflayer_Weaponsmith_Cleave", math.random(14000, 16000), 0)
pUnit:RegisterEvent("Dragonflayer_Weaponsmith_Concussion_Blow", 30000, 0)
pUnit:RegisterEvent("Dragonflayer_Weaponsmith_Disarm", math.random(17000, 24000), 0)
end

function Dragonflayer_Weaponsmith_OnLeaveCombat(pUnit, Event)
pUnit:RemoveEvents()
end

function Dragonflayer_Weaponsmith_OnDeath(pUnit, Event)
pUnit:RemoveEvents()
end

RegisterUnitEvent(24080, 1, "Dragonflayer_Weaponsmith_OnCombat")
RegisterUnitEvent(24080, 2, "Dragonflayer_Weaponsmith_OnLeaveCombat")
RegisterUnitEvent(24080, 4, "Dragonflayer_Weaponsmith_OnDeath")

function Dragonflayer_Weaponsmith_Cleave(pUnit, Event)
pUnit:FullCastSpellOnTarget(42724, pUnit:GetMainTank())
end

function Dragonflayer_Weaponsmith_Concussion_Blow(pUnit, Event)
pUnit:FullCastSpellOnTarget(22427, pUnit:GetMainTank())
end

function Dragonflayer_Weaponsmith_Disarm(pUnit, Event)
pUnit:FullCastSpellOnTarget(6713, pUnit:GetMainTank())
end
