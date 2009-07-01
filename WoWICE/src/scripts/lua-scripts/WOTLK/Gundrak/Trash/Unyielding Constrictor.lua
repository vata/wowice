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

function Unyielding_Constrictor_OnCombat(pUnit, Event)
pUnit:RegisterEvent("Unyielding_Constrictor_Vicious_Bite", math.random(17000, 19000), 0)
end

function Unyielding_Constrictor_OnLeaveCombat(pUnit, Event)
pUnit:RemoveEvents()
end

function Unyielding_Constrictor_OnKillTarget(pUnit, Event)
end

function Unyielding_Constrictor_OnDeath(pUnit, Event)
pUnit:RemoveEvents()
end

RegisterUnitEvent(29768, 1, "Unyielding_Constrictor_OnCombat")
RegisterUnitEvent(29768, 2, "Unyielding_Constrictor_OnLeaveCombat")
RegisterUnitEvent(29768, 3, "Unyielding_Constrictor_OnKillTarget")
RegisterUnitEvent(29768, 4, "Unyielding_Constrictor_OnDeath")

function Unyielding_Constrictor_Vicious_Bite(pUnit, Event)
pUnit:FullCastSpellOnTarget(55602, pUnit:GetMainTank())
end
