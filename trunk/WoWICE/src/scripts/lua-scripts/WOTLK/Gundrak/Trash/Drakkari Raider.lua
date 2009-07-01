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

function Drakkari_Raider_OnCombat(pUnit, Event)
pUnit:RegisterEvent("Drakkari_Raider_Cleave", math.random(14000, 22000), 0)
end

function Drakkari_Raider_OnLeaveCombat(pUnit, Event)
pUnit:RemoveEvents()
end

function Drakkari_Raider_OnKillTarget(pUnit, Event)
end

function Drakkari_Raider_OnDeath(pUnit, Event)
pUnit:RemoveEvents()
end

RegisterUnitEvent(29982, 1, "Drakkari_Raider_OnCombat")
RegisterUnitEvent(29982, 2, "Drakkari_Raider_OnLeaveCombat")
RegisterUnitEvent(29982, 3, "Drakkari_Raider_OnKillTarget")
RegisterUnitEvent(29982, 4, "Drakkari_Raider_OnDeath")

function Drakkari_Raider_Cleave(pUnit, Event)
pUnit:FullCastSpellOnTarget(15496, pUnit:GetMainTank())
end
