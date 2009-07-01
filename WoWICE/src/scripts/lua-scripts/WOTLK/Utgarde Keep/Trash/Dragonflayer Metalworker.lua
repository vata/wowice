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

function Dragonflayer_Metalworker_OnCombat(pUnit, Event)
pUnit:RegisterEvent("Dragonflayer_Metalworker_Enrage", math.random(30000, 34000), 1)
pUnit:RegisterEvent("Dragonflayer_Metalworker_Sunder_Armor", math.random(9000, 12000), 0)
end

function Dragonflayer_Metalworker_OnLeaveCombat(pUnit, Event)
pUnit:RemoveEvents()
end

function Dragonflayer_Metalworker_OnDeath(pUnit, Event)
pUnit:RemoveEvents()
end

RegisterUnitEvent(24078, 1, "Dragonflayer_Metalworker_OnCombat")
RegisterUnitEvent(24078, 2, "Dragonflayer_Metalworker_OnLeaveCombat")
RegisterUnitEvent(24078, 4, "Dragonflayer_Metalworker_OnDeath")

function Dragonflayer_Metalworker_Enrage(pUnit, Event)
pUnit:FullCastSpell(8599)
end

function Dragonflayer_Metalworker_Sunder_Armor(pUnit, Event)
pUnit:FullCastSpellOnTarget(15572, pUnit:GetMainTank())
end
