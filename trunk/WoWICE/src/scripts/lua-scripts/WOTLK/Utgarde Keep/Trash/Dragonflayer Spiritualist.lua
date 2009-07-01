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

function Dragonflayer_Spiritualist_OnCombat(pUnit, Event)
pUnit:RegisterEvent("Dragonflayer_Spiritualist_Flame_Shock", math.random(9000, 12000), 0)
pUnit:RegisterEvent("Dragonflayer_Spiritualist_Lightning_Bolt", math.random(5000, 7000), 0)
pUnit:RegisterEvent("Dragonflayer_Spiritualist_Healing_Wave", 20000, 0)
end

function Dragonflayer_Spiritualist_OnLeaveCombat(pUnit, Event)
pUnit:RemoveEvents()
end

function Dragonflayer_Spiritualist_OnDeath(pUnit, Event)
pUnit:RemoveEvents()
end

RegisterUnitEvent(28410, 1, "Dragonflayer_Spiritualist_OnCombat")
RegisterUnitEvent(28410, 2, "Dragonflayer_Spiritualist_OnLeaveCombat")
RegisterUnitEvent(28410, 4, "Dragonflayer_Spiritualist_OnDeath")

function Dragonflayer_Spiritualist_Flame_Shock(pUnit, Event)
pUnit:FullCastSpellOnTarget(51588, pUnit:GetRandomPlayer(0))
end

function Dragonflayer_Spiritualist_Lightning_Bolt(pUnit, Event)
pUnit:FullCastSpellOnTarget(51587, pUnit:GetMainTank())
end

function Dragonflayer_Spiritualist_Healing_Wave(pUnit, Event)
if pUnit:GetHealthPct() <= 50 then
pUnit:FullCastSpell(51586)
end
end
