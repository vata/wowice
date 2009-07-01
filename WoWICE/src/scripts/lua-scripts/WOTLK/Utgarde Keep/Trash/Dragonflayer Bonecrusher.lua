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

function Dragonflayer_Bonecrusher_OnCombat(pUnit, Event)
pUnit:RegisterEvent("Dragonflayer_Bonecrusher_Head_Crack", 24000, 0)
pUnit:RegisterEvent("Dragonflayer_Bonecrusher_Knockdown_Spin", math.random(12000, 16000), 0)
end

function Dragonflayer_Bonecrusher_OnLeaveCombat(pUnit, Event)
pUnit:RemoveEvents()
end

function Dragonflayer_Bonecrusher_OnDeath(pUnit, Event)
pUnit:RemoveEvents()
end

RegisterUnitEvent(24069, 1, "Dragonflayer_Bonecrusher_OnCombat")
RegisterUnitEvent(24069, 2, "Dragonflayer_Bonecrusher_OnLeaveCombat")
RegisterUnitEvent(24069, 4, "Dragonflayer_Bonecrusher_OnDeath")

function Dragonflayer_Bonecrusher_Head_Crack(pUnit, Event)
pUnit:FullCastSpellOnTarget(9791, pUnit:GetMainTank())
end

function Dragonflayer_Bonecrusher_Knockdown_Spin(pUnit, Event)
pUnit:FullCastSpell(43935)
end
