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

function Enslaved_ProtoDrake_OnCombat(pUnit, Event)
pUnit:RegisterEvent("Enslaved_ProtoDrake_Flame_Breath", math.random(9000, 12000), 0)
pUnit:RegisterEvent("Enslaved_ProtoDrake_Knock_Away", math.random(25000, 27000), 0)
pUnit:RegisterEvent("Enslaved_ProtoDrake_Rend", 15000, 0)
end

function Enslaved_ProtoDrake_OnLeaveCombat(pUnit, Event)
pUnit:RemoveEvents()
end

function Enslaved_ProtoDrake_OnDeath(pUnit, Event)
pUnit:RemoveEvents()
end

RegisterUnitEvent(24083, 1, "Enslaved_ProtoDrake_OnCombat")
RegisterUnitEvent(24083, 2, "Enslaved_ProtoDrake_OnLeaveCombat")
RegisterUnitEvent(24083, 4, "Enslaved_ProtoDrake_OnDeath")

function Enslaved_ProtoDrake_Flame_Breath(pUnit, Event)
pUnit:FullCastSpell(50653)
end

function Enslaved_ProtoDrake_Knock_Away(pUnit, Event)
pUnit:FullCastSpellOnTarget(49722, pUnit:GetMainTank())
end

function Enslaved_ProtoDrake_Rend(pUnit, Event)
pUnit:FullCastSpellOnTarget(43931, pUnit:GetMainTank())
end
