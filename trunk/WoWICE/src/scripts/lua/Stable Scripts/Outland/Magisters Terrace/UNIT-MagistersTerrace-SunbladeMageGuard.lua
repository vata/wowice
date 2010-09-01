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

function SunbladeMageGuard_OnCombat(Unit, Event)
	Unit:RegisterAIUpdateEvent(7000)
end

function SunbladeMageGuard_GlaiveThrow(Unit)
	local FlipGlaive = math.random(2)
	if FlipGlaive ==1 and Unit:GetRandomPlayer(7) then
		Unit:CastSpellOnTarget(44478, Unit:GetRandomPlayer(7))
	else
		Unit:CastSpellOnTarget(46028, Unit:GetRandomPlayer(7))
	end
end

function SunbladeMageGuard_LeaveCombat(Unit, Event)
	Unit:RemoveAIUpdateEvent()
end

function SunbladeMageGuard_Died(Unit, Event)
	Unit:RemoveAIUpdateEvent()
end



RegisterUnitEvent(24683, 1, "SunbladeMageGuard_OnCombat")
RegisterUnitEvent(24683, 21, "SunbladeMageGuard_GlaiveThrow")
RegisterUnitEvent(24683, 2, "SunbladeMageGuard_LeaveCombat")
RegisterUnitEvent(24683, 4, "SunbladeMageGuard_Died")
