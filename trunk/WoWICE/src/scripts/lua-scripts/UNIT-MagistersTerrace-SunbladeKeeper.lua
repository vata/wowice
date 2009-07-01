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

function SunbladeKeeper_OnCombat(Unit, Event)
Unit:RegisterEvent("SunbladeKeeper_ShadowBolt", 6000, 40)
end

function SunbladeKeeper_ShadowBolt(Unit, Event)
local boltcheck = Unit:GetRandomPlayer(7)
if (boltcheck ~= nil) then
Unit:FullCastSpellOnTarget(15232, Unit:GetRandomPlayer(7))
end
end


function SunbladeKeeper_LeaveCombat(Unit, Event)
Unit:RemoveEvents()
end

function SunbladeKeeper_Died(Unit, Event)
Unit:RemoveEvents()
end


RegisterUnitEvent(24762, 1, "SunbladeKeeper_OnCombat")
RegisterUnitEvent(24762, 2, "SunbladeKeeper_LeaveCombat")
RegisterUnitEvent(24762, 4, "SunbladeKeeper_Died")
