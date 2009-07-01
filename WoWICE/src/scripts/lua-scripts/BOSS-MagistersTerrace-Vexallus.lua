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

function Vexallus_Combat(Unit, Event)
--Unit:RegisterEvent("Vexallus_Chain", 5400, 0)
Unit:RegisterEvent("Vexallus_SpawnPhases", 1000, 1)
Unit:RegisterEvent("Vexallus_ArcaneShock", 4000, 0)
Unit:RegisterEvent("Vexallus_Overload", math.random(2000, 3000), 0)
end

--[[
Not working hits himself.

function Vexallus_Chain(Unit, Event)
local Flip = math.random(1,3)
if Flip == 1 then
Unit:CastSpellOnTarget(44318, Unit:GetRandomPlayer(7))
else
end
end--]]

function Vexallus_ArcaneShock(Unit, Event)
local Flip = math.random(1,2)
if Flip == 1 then
Unit:CastSpellOnTarget(46381, Unit:GetRandomPlayer(0))
else
end
end

function Vexallus_Overload(Unit, Event)
if Unit:GetHealthPct() <= 10 then
Unit:CastSpell(44353)
end
end


--wowhead: 85%, 70%, 55%, 40%, and 25% Spawns.
function Vexallus_SpawnPhases(Unit, Event)
Unit:RegisterEvent("Vexallus_85", 1000, 0)
Unit:RegisterEvent("Vexallus_70", 1000, 0)
Unit:RegisterEvent("Vexallus_55", 1000, 0)
Unit:RegisterEvent("Vexallus_40", 1000, 0)
Unit:RegisterEvent("Vexallus_25", 1000, 0)
end 


--85
function Vexallus_85(Unit, Event)
if Unit:GetHealthPct() <= 85 and Done_85 ~= 1 then
local x = Unit:GetX()
local y = Unit:GetY()
local z = Unit:GetZ()
local o = Unit:GetO()
Unit:SpawnCreature(24745, x, y, z, o, 16, 0)
Done_85 = 1
else
end
end
--end

--70
function Vexallus_70(Unit, Event)
if Unit:GetHealthPct() <= 70 and  Done_70 ~= 1 then
local x = Unit:GetX()
local y = Unit:GetY()
local z = Unit:GetZ()
local o = Unit:GetO()
Unit:SpawnCreature(24745, x, y, z, o, 16, 0)
Done_70 = 1
end
end
--end

--55
function Vexallus_55(Unit, Event)
if Unit:GetHealthPct() <= 55 and Done_55 ~= 1 then
local x = Unit:GetX()
local y = Unit:GetY()
local z = Unit:GetZ()
local o = Unit:GetO()
Unit:SpawnCreature(24745, x, y, z, o, 16, 0)
Done_55 = 1
end
end
--end
--40
function Vexallus_40(Unit, Event)
if Unit:GetHealthPct() <= 40 and Done_40 ~= 1 then
local x = Unit:GetX()
local y = Unit:GetY()
local z = Unit:GetZ()
local o = Unit:GetO()
Unit:SpawnCreature(24745, x, y, z, o, 16, 0)
Done_40 = 1
end
end
--end
--25
function Vexallus_25(Unit, Event)
if Unit:GetHealthPct() <= 25 and Done_25 ~= 1 then
local x = Unit:GetX()
local y = Unit:GetY()
local z = Unit:GetZ()
local o = Unit:GetO()
Unit:SpawnCreature(24745, x, y, z, o, 16, 0)
Done_25 = 1
end
end
--end









--Remove Events Functions

function Vexallus_LeaveCombat(Unit, Event)
Unit:RemoveEvents()
end

function Vexallus_Died(Unit, Event)
Unit:RemoveEvents()
end


RegisterUnitEvent(24744, 1, "Vexallus_Combat")
RegisterUnitEvent(24744, 2, "Vexallus_LeaveCombat")
RegisterUnitEvent(24744, 4, "Vexallus_Died")