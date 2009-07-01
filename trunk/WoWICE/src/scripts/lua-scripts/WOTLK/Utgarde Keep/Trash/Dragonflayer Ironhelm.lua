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

function Dragonflayer_Ironhelm_OnCombat(pUnit, Event)
pUnit:RegisterEvent("Dragonflayer_Ironhelm_Heroic_Strike", 5000, 0)
pUnit:RegisterEvent("Dragonflayer_Ironhelm_Ringing_Slap", math.random(12000, 15000), 0)
end

function Dragonflayer_Ironhelm_OnLeaveCombat(pUnit, Event)
pUnit:RemoveEvents()
end

function Dragonflayer_Ironhelm_OnDeath(pUnit, Event)
pUnit:RemoveEvents()
end

RegisterUnitEvent(23961, 1, "Dragonflayer_Ironhelm_OnCombat")
RegisterUnitEvent(23961, 2, "Dragonflayer_Ironhelm_OnLeaveCombat")
RegisterUnitEvent(23961, 4, "Dragonflayer_Ironhelm_OnDeath")

function Dragonflayer_Ironhelm_Heroic_Strike(pUnit, Event)
pUnit:FullCastSpellOnTarget(29426, pUnit:GetMainTank())
end

function Dragonflayer_Ironhelm_Ringing_Slap(pUnit, Event)
pUnit:FullCastSpellOnTarget(42780, pUnit:GetMainTank())
end
