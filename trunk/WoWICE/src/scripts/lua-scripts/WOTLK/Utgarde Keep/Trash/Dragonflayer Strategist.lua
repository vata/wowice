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

function Dragonflayer_Strategist_OnCombat(pUnit, Event)
pUnit:RegisterEvent("Dragonflayer_Strategist_Blind", math.random(12000, 15000), 0)
pUnit:RegisterEvent("Dragonflayer_Strategist_Hurl_Dagger", math.random(3000, 6000), 0)
pUnit:RegisterEvent("Dragonflayer_Strategist_Ticking_Bomb", math.random(20000, 24000), 0)
end

function Dragonflayer_Strategist_OnLeaveCombat(pUnit, Event)
pUnit:RemoveEvents()
end

function Dragonflayer_Strategist_OnDeath(pUnit, Event)
pUnit:RemoveEvents()
end

RegisterUnitEvent(23956, 1, "Dragonflayer_Strategist_OnCombat")
RegisterUnitEvent(23956, 2, "Dragonflayer_Strategist_OnLeaveCombat")
RegisterUnitEvent(23956, 4, "Dragonflayer_Strategist_OnDeath")

function Dragonflayer_Strategist_Blind(pUnit, Event)
pUnit:FullCastSpellOnTarget(42972, pUnit:GetRandomPlayer(0))
end

function Dragonflayer_Strategist_Hurl_Dagger(pUnit, Event)
pUnit:FullCastSpellOnTarget(42772, pUnit:GetMainTank())
end

function Dragonflayer_Strategist_Ticking_Bomb(pUnit, Event)
pUnit:FullCastSpellOnTarget(54955, pUnit:GetRandomPlayer(0))
end
