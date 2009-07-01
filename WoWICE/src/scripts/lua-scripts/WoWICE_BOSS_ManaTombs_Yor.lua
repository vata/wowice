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

--Scripted: recon
function Yor_Fire(pUnit, Event)
	print "Yor Double Breath"
	pUnit:FullCastSpellOnTarget(38361,Unit:GetClosestPlayer(0))
end

function Yor_stomp(pUnit, Event)
	print "Yor stomp"
	pUnit:CastSpell(36405)
end

function Yor_OnCombat(pUnit, Event)
	print "Yor"
	pUnit:RegisterEvent("Yor_Fire",10000,0)
	pUnit:RegisterEvent("Yor_stomp",13000,0)
end


function Yor_OnLeaveCombat(pUnit, Event)
	pUnit:RemoveEvents()	
end

function Yor_OnDied(pUnit, Event)
	pUnit:RemoveEvents()
end


RegisterUnitEvent(22930, 1, "Yor_OnCombat")
RegisterUnitEvent(22930, 2, "Yor_OnLeaveCombat")
RegisterUnitEvent(22930, 3, "Yor_OnDied")