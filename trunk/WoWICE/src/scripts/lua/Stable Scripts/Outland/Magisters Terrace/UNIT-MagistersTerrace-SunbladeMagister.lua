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

function SunbladeMagister_OnCombat(Unit, Event)
	Unit:RegisterAIUpdateEvent(3000)
end

function SunbladeMagister_Frostbolt(Unit, Event)
	local plr = Unit:GetRandomPlayer(1)
	if plr then
		Unit:FullCastSpellOnTarget(46035,plr)
	end
end

function SunbladeMagister_ArcaneNova(Unit)
	local arcaneflip = math.random(6)
	local plr = Unit:GetRandomPlayer(7)
	if arcaneflip == 1 and plr ~= nil then
		Unit:FullCastSpellOnTarget(46036,plr)
	else
	end
end

function SunbladeMagister_LeaveCombat(Unit)
	Unit:RemoveEvents()
	Unit:RemoveAIUpdateEvent()
end

function SunbladeMagister_Died(Unit)
	Unit:RemoveEvents()
	Unit:RemoveAIUpdateEvent()
end


RegisterUnitEvent(24685, 1, "SunbladeMagister_OnCombat")
RegisterUnitEvent(24685, 21,"SunbladeMagister_Frostbolt")
RegisterUnitEvent(24685, 21,"SunbladeMagister_ArcaneNova")
RegisterUnitEvent(24685, 2, "SunbladeMagister_LeaveCombat")
RegisterUnitEvent(24685, 4, "SunbladeMagister_Died")
