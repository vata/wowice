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

function SunbladeWarlock_OnCombat(Unit, Event)
--He summons the Imp
Unit:CastSpell(44517)
--Cast Events don't know how long the cooldown is.
Unit:RegisterEvent("SunbladeWarlock_Incinerate", 5000, 0)
--46042 Immolate
Unit:RegisterEvent("SunbladeWarlock_Immolate", 3500, 0)
end

function SunbladeWarlock_Incinerate(Unit, Event)
local incCheck = Unit:GetClosestPlayer()
if (incCheck ~= nil) then
Unit:FullCastSpellOnTarget(46043, Unit:GetClosestPlayer())
end
end


function SunbladeWarlock_Immolate(Unit, Event)
local Flip = math.random(1,3)
local immCheck = Unit:GetMainTank()
if (immCheck ~= nil) then
if Flip == 1 then
Unit:FullCastSpellOnTarget(46042, Unit:GetMainTank())
else
local Flip = nil
end
end
end

function SunbladeWarlock_LeaveCombat(Unit, Event)
Unit:RemoveEvents()
end

function SunbladeWarlock_Died(Unit, Event)
Unit:RemoveEvents()
end


RegisterUnitEvent(24686, 1, "SunbladeWarlock_OnCombat")
RegisterUnitEvent(24686, 2, "SunbladeWarlock_LeaveCombat")
RegisterUnitEvent(24686, 4, "SunbladeWarlock_Died")
