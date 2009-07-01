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

function Dragonflayer_Runecaster_OnCombat(pUnit, Event)
pUnit:RegisterEvent("Dragonflayer_Runecaster_Bolthorns_Rune_of_Flame", 10000, 0)
pUnit:RegisterEvent("Dragonflayer_Runecaster_Njords_Rune_of_Protection", math.random(20000, 25000), 0)
end

function Dragonflayer_Runecaster_OnLeaveCombat(pUnit, Event)
pUnit:RemoveEvents()
end

function Dragonflayer_Runecaster_OnDeath(pUnit, Event)
pUnit:RemoveEvents()
end

RegisterUnitEvent(23960, 1, "Dragonflayer_Runecaster_OnCombat")
RegisterUnitEvent(23960, 2, "Dragonflayer_Runecaster_OnLeaveCombat")
RegisterUnitEvent(23960, 4, "Dragonflayer_Runecaster_OnDeath")

function Dragonflayer_Runecaster_Bolthorns_Rune_of_Flame(pUnit, Event)
pUnit:FullCastSpell(54965)
end

function Dragonflayer_Runecaster_Njords_Rune_of_Protection(pUnit, Event)
pUnit:FullCastSpell(42740)
end
