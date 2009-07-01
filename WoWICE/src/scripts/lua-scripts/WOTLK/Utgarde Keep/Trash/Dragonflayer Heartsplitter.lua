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

function Dragonflayer_Heartsplitter_OnCombat(pUnit, Event)
pUnit:RegisterEvent("Dragonflayer_Heartsplitter_Piercing_Jab", math.random(16000, 18000), 0)
pUnit:RegisterEvent("Dragonflayer_Heartsplitter_Throw", math.random(5000, 7000), 0)
pUnit:RegisterEvent("Dragonflayer_Heartsplitter_Wing_Clip", 13000, 0)
end

function Dragonflayer_Heartsplitter_OnLeaveCombat(pUnit, Event)
pUnit:RemoveEvents()
end

function Dragonflayer_Heartsplitter_OnDeath(pUnit, Event)
pUnit:RemoveEvents()
end

RegisterUnitEvent(24071, 1, "Dragonflayer_Heartsplitter_OnCombat")
RegisterUnitEvent(24071, 2, "Dragonflayer_Heartsplitter_OnLeaveCombat")
RegisterUnitEvent(24071, 4, "Dragonflayer_Heartsplitter_OnDeath")

function Dragonflayer_Heartsplitter_Piercing_Jab(pUnit, Event)
pUnit:FullCastSpellOnTarget(31551, pUnit:GetMainTank())
end

function Dragonflayer_Heartsplitter_Throw(pUnit, Event)
pUnit:FullCastSpellOnTarget(43665, pUnit:GetRandomPlayer(0))
end

function Dragonflayer_Heartsplitter_Wing_Clip(pUnit, Event)
pUnit:FullCastSpellOnTarget(32908, pUnit:GetClosestPlayer())
end
