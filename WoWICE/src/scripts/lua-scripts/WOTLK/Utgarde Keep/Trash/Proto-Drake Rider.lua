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

function ProtoDrake_Rider_OnCombat(pUnit, Event)
pUnit:RegisterEvent("ProtoDrake_Rider_Piercing_Jab", math.random(16000, 18000), 0)
pUnit:RegisterEvent("ProtoDrake_Rider_Throw", math.random(6000, 8000), 0)
pUnit:RegisterEvent("ProtoDrake_Rider_Wing_Clip", 12000, 0)
end

function ProtoDrake_Rider_OnLeaveCombat(pUnit, Event)
pUnit:RemoveEvents()
end

function ProtoDrake_Rider_OnDeath(pUnit, Event)
pUnit:RemoveEvents()
end

RegisterUnitEvent(24849, 1, "ProtoDrake_Rider_OnCombat")
RegisterUnitEvent(24849, 2, "ProtoDrake_Rider_OnLeaveCombat")
RegisterUnitEvent(24849, 4, "ProtoDrake_Rider_OnDeath")

function ProtoDrake_Rider_Piercing_Jab(pUnit, Event)
pUnit:FullCastSpellOnTarget(31551, pUnit:GetMainTank())
end

function ProtoDrake_Rider_Throw(pUnit, Event)
pUnit:FullCastSpellOnTarget(43665, pUnit:GetRandomPlayer(0))
end

function ProtoDrake_Rider_Wing_Clip(pUnit, Event)
pUnit:FullCastSpellOnTarget(32908, pUnit:GetMainTank())
end
