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

function Dragonflayer_Overseer_OnCombat(pUnit, Event)
pUnit:RegisterEvent("Dragonflayer_Overseer_Battle_Shout", math.random(22000, 25000), 0)
pUnit:RegisterEvent("Dragonflayer_Overseer_Charge", 10000, 0)
pUnit:RegisterEvent("Dragonflayer_Overseer_Demoralizing_Shout", 30000, 0)
end

function Dragonflayer_Overseer_OnLeaveCombat(pUnit, Event)
pUnit:RemoveEvents()
end

function Dragonflayer_Overseer_OnDeath(pUnit, Event)
pUnit:RemoveEvents()
end

RegisterUnitEvent(24085, 1, "Dragonflayer_Overseer_OnCombat")
RegisterUnitEvent(24085, 2, "Dragonflayer_Overseer_OnLeaveCombat")
RegisterUnitEvent(24085, 4, "Dragonflayer_Overseer_OnDeath")

function Dragonflayer_Overseer_Battle_Shout(pUnit, Event)
pUnit:FullCastSpell(38232)
end

function Dragonflayer_Overseer_Charge(pUnit, Event)
pUnit:FullCastSpellOnTarget(35570, pUnit:GetRandomPlayer(0))
end

function Dragonflayer_Overseer_Demoralizing_Shout(pUnit, Event)
pUnit:FullCastSpell(16244)
end
