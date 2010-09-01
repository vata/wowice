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

function SunbladeSisterofTorment_OnCombat(Unit, Event)
	Unit:RegisterEvent("SunbladeSisterofTorment_DeadlyEmbrace", 10000, 0)
	Unit:RegisterEvent("SunbladeSisterofTorment_LashofPain",7000, 0) 
end

--Deadly Embrace
function SunbladeSisterofTorment_DeadlyEmbrace(Unit, Event)
	if Unit:GetRandomPlayer(1) then
		Unit:FullCastSpellOnTarget(44547, Unit:GetRandomPlayer(1))
	end
end

--44640 Lash of Pain
function SunbladeSisterofTorment_LashofPain(Unit, Event)
	local Flip = math.random(2)
	if Flip == 1 and Unit:GetClosestPlayer() then
		Unit:CastSpellOnTarget(44640, Unit:GetClosestPlayer())
	end
end


function SunbladeSisterofTorment_LeaveCombat(Unit, Event)
	Unit:RemoveEvents()
end

function SunbladeSisterofTorment_Died(Unit, Event)
	Unit:RemoveEvents()
end


RegisterUnitEvent(24697, 1, "SunbladeSisterofTorment_OnCombat")
RegisterUnitEvent(24697, 2, "SunbladeSisterofTorment_LeaveCombat")
RegisterUnitEvent(24697, 4, "SunbladeSisterofTorment_Died")
