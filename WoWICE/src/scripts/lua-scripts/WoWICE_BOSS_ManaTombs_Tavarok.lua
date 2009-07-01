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

function Tavarok_Earthquake(pUnit, Event)
	print "Tavarok Earthquake"
	pUnit:CastSpell(33919)
	pUnit:SendChatMessage(11, 0, "Do you feel my Earthquake...")
end

function Tavarok_Crystal_Poison(pUnit, Event)
	print "Tavarok Crystal Poison"
	pUnit:FullCastSpellOnTarget(32361,Unit:GetRandomPlayer(0))
	pUnit:SendChatMessage(11, 0, "Some poison...")
end
--  Heroic spell --
function Tavarok_smash(pUnit, Event)
	print "Tavarok_smash"
	pUnit:CastSpellOnTarget(38761,pUnit:GetClosestPlayer(0))
end

function Tavarok_OnCombat(pUnit, Event)
	print "Tavarok"
	pUnit:RegisterEvent("Tavarok_Earthquake",10000,0)
	pUnit:RegisterEvent("Tavarok_Crystal_Poison",13000,0)
	pUnit:RegisterEvent("Tavarok_smash",13000,0)
end

function Tavarok_OnKilledTarget (pUnit, Event)
	
end

function Tavarok_OnLeaveCombat(pUnit, Event)
	pUnit:RemoveEvents()	
end

function Tavarok_OnDied(pUnit, Event)
	pUnit:RemoveEvents()
end

RegisterUnitEvent(18343, 1, "Tavarok_OnCombat")
RegisterUnitEvent(18343, 2, "Tavarok_OnLeaveCombat")
RegisterUnitEvent(18343, 3, "Tavarok_OnKilledTarget")
RegisterUnitEvent(18343, 4, "Tavarok_OnDied")