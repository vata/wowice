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

function Drakkari_Rhino_OnCombat(pUnit, Event)
pUnit:RegisterEvent("Drakkari_Rhino_Charge", math.random(15000, 18000), 0)
pUnit:RegisterEvent("Drakkari_Rhino_Deafening_Roar", math.random(20000, 23000), 0)
end

function Drakkari_Rhino_OnLeaveCombat(pUnit, Event)
pUnit:RemoveEvents()
end

function Drakkari_Rhino_OnKillTarget(pUnit, Event)
end

function Drakkari_Rhino_OnDeath(pUnit, Event)
pUnit:RemoveEvents()
end

RegisterUnitEvent(29838, 1, "Drakkari_Rhino_OnCombat")
RegisterUnitEvent(29838, 2, "Drakkari_Rhino_OnLeaveCombat")
RegisterUnitEvent(29838, 3, "Drakkari_Rhino_OnKillTarget")
RegisterUnitEvent(29838, 4, "Drakkari_Rhino_OnDeath")

function Drakkari_Rhino_Charge(pUnit, Event)
pUnit:FullCastSpellOnTarget(55530, pUnit:GetRandomPlayer(0))
end

function Drakkari_Rhino_Deafening_Roar(pUnit, Event)
pUnit:FullCastSpell(55663)
end
