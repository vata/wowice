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

function Spitting_Cobra_OnCombat(pUnit, Event)
pUnit:RegisterEvent("Spitting_Cobra_Cobra_Strike", math.random(25000, 28000), 0)
pUnit:RegisterEvent("Spitting_Cobra_Venom_Spit", math.random(14000, 18000), 0)
end

function Spitting_Cobra_OnLeaveCombat(pUnit, Event)
pUnit:RemoveEvents()
end

function Spitting_Cobra_OnKillTarget(pUnit, Event)
end

function Spitting_Cobra_OnDeath(pUnit, Event)
pUnit:RemoveEvents()
end

RegisterUnitEvent(29774, 1, "Spitting_Cobra_OnCombat")
RegisterUnitEvent(29774, 2, "Spitting_Cobra_OnLeaveCombat")
RegisterUnitEvent(29774, 3, "Spitting_Cobra_OnKillTarget")
RegisterUnitEvent(29774, 4, "Spitting_Cobra_OnDeath")

function Spitting_Cobra_Cobra_Strike(pUnit, Event)
pUnit:FullCastSpellOnTarget(55703, pUnit:GetMainTank())
end

function Spitting_Cobra_Venom_Spit(pUnit, Event)
pUnit:FullCastSpellOnTarget(55700, pUnit:GetRandomPlayer(0))
end
