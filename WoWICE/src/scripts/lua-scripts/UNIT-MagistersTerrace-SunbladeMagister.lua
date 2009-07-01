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

function SunbladeMagister_OnCombat(Unit, Event)
Unit:RegisterEvent("SunbladeMagister_Frostbolt", 3000, 40)
Unit:RegisterEvent("SunbladeMagister_ArcaneNova", 3000, 40)
end

function SunbladeMagister_Frostbolt(Unit, Event)
local frostCheck = Unit:GetRandomPlayer(1)
if (frostCheck ~= nil) then
Unit:FullCastSpellOnTarget(46035, Unit:GetRandomPlayer(1))
end
end

function SunbladeMagister_ArcaneNova(Unit, Event)
ArcaneFlip=math.random(1, 6)
local arcaneCheck = Unit:GetRandomPlayer(7)
if (arcaneCheck ~= nil) then
if ArcaneFlip==1 then
Unit:FullCastSpellOnTarget(46036, Unit:GetRandomPlayer(7))
else
ArcaneFlip=nil
end
end
end

function SunbladeMagister_LeaveCombat(Unit, Event)
Unit:RemoveEvents()
end

function SunbladeMagister_Died(Unit, Event)
Unit:RemoveEvents()
end


RegisterUnitEvent(24685, 1, "SunbladeMagister_OnCombat")
RegisterUnitEvent(24685, 2, "SunbladeMagister_LeaveCombat")
RegisterUnitEvent(24685, 4, "SunbladeMagister_Died")
