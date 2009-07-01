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

function Drakkari_Battle_Rider_OnCombat(pUnit, Event)
pUnit:RegisterEvent("Drakkari_Battle_Rider_Poisoned_Spear", math.random(23000, 27000), 0)
pUnit:RegisterEvent("Drakkari_Battle_Rider_Throw", math.random(11000, 15000), 0)
end

function Drakkari_Battle_Rider_OnLeaveCombat(pUnit, Event)
pUnit:RemoveEvents()
end

function Drakkari_Battle_Rider_OnKillTarget(pUnit, Event)
end

function Drakkari_Battle_Rider_OnDeath(pUnit, Event)
pUnit:RemoveEvents()
end

RegisterUnitEvent(29836, 1, "Drakkari_Battle_Rider_OnCombat")
RegisterUnitEvent(29836, 2, "Drakkari_Battle_Rider_OnLeaveCombat")
RegisterUnitEvent(29836, 3, "Drakkari_Battle_Rider_OnKillTarget")
RegisterUnitEvent(29836, 4, "Drakkari_Battle_Rider_OnDeath")

function Drakkari_Battle_Rider_Poisoned_Spear(pUnit, Event)
pUnit:FullCastSpellOnTarget(55521, pUnit:GetRandomPlayer(0))
end

function Drakkari_Battle_Rider_Throw(pUnit, Event)
pUnit:FullCastSpellOnTarget(55348, pUnit:GetMainTank())
end
