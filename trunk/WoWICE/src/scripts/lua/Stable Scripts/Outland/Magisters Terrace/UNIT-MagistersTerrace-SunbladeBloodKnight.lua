--[[
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
 *]]

function SunbladeBloodKnight_OnCombat(Unit, Event)
	Unit:RegisterAIUpdateEvent(10000)
end

--[[-- I dont't know how often he does this just set it to 6, 3 sec--]]
function SunbladeBloodKnight_HolyLight(Unit, Event)
	Unit:FullCastSpell(27136)
end

function SunbladeBloodKnight_LeaveCombat(Unit, Event)
	Unit:RemoveAIUpdateEvent()
end

function SunbladeBloodKnight_Died(Unit, Event)
	Unit:RemoveAIUpdateEvent()
end


RegisterUnitEvent(27136, 1, "SunbladeBloodKnight_OnCombat")
RegisterUnitEvent(27136, 21, "SunbladeBloodKnight_HolyLight")
RegisterUnitEvent(27136, 2, "SunbladeBloodKnight_LeaveCombat")
RegisterUnitEvent(27136, 4, "SunbladeBloodKnight_Died")
