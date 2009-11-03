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
--HORDE
--Undercity

function TaxiUC_Combat(Unit, Event)
local x = Unit:GetX()
local y = Unit:GetY()
local z = Unit:GetZ()
local o = Unit:GetO()
Unit:SpawnCreature(9521, x, y, z, o, 68, 60000)
Unit:SpawnCreature(9521, x, y, z, o, 68, 60000)
Unit:SpawnCreature(9521, x, y, z, o, 68, 60000)
Unit:SpawnCreature(9521, x, y, z, o, 68, 60000)
Unit:SpawnCreature(9521, x, y, z, o, 68, 60000)
Unit:SpawnCreature(9521, x, y, z, o, 68, 60000)
end

function TaxiUC_LeaveCombat(Unit, Event)
Unit:RemoveEvents()
end

function TaxiUC_Died(Unit, Event)
Unit:RemoveEvents()
end


RegisterUnitEvent(4551, 1, "TaxiUC_Combat")
RegisterUnitEvent(4551, 2, "TaxiUC_LeaveCombat")
RegisterUnitEvent(4551, 4, "TaxiUC_Died")

--Thunderbluff

function TaxiTB_Combat(Unit, Event)
local x = Unit:GetX()
local y = Unit:GetY()
local z = Unit:GetZ()
local o = Unit:GetO()
Unit:SpawnCreature(9297, x, y, z, o, 83, 60000)
Unit:SpawnCreature(9297, x, y, z, o, 83, 60000)
Unit:SpawnCreature(9297, x, y, z, o, 83, 60000)
Unit:SpawnCreature(9297, x, y, z, o, 83, 60000)
Unit:SpawnCreature(9297, x, y, z, o, 83, 60000)
Unit:SpawnCreature(9297, x, y, z, o, 83, 60000)
end

function TaxiTB_LeaveCombat(Unit, Event)
Unit:RemoveEvents()
end

function TaxiTB_Died(Unit, Event)
Unit:RemoveEvents()
end


RegisterUnitEvent(2995, 1, "TaxiTB_Combat")
RegisterUnitEvent(2995, 2, "TaxiTB_LeaveCombat")
RegisterUnitEvent(2995, 4, "TaxiTB_Died")

--Silvermoon

function TaxiSM_Combat(Unit, Event)
local x = Unit:GetX()
local y = Unit:GetY()
local z = Unit:GetZ()
local o = Unit:GetO()
Unit:SpawnCreature(9521, x, y, z, o, 1602, 60000)
Unit:SpawnCreature(9521, x, y, z, o, 1602, 60000)
Unit:SpawnCreature(9521, x, y, z, o, 1602, 60000)
Unit:SpawnCreature(9521, x, y, z, o, 1602, 60000)
Unit:SpawnCreature(9521, x, y, z, o, 1602, 60000)
Unit:SpawnCreature(9521, x, y, z, o, 1602, 60000)
end

function TaxiSM_LeaveCombat(Unit, Event)
Unit:RemoveEvents()
end

function TaxiSM_Died(Unit, Event)
Unit:RemoveEvents()
end


RegisterUnitEvent(16192, 1, "TaxiSM_Combat")
RegisterUnitEvent(16192, 2, "TaxiSM_LeaveCombat")
RegisterUnitEvent(16192, 4, "TaxiSM_Died")


--Orgimmar

function TaxiOG_Combat(Unit, Event)
local x = Unit:GetX()
local y = Unit:GetY()
local z = Unit:GetZ()
local o = Unit:GetO()
Unit:SpawnCreature(9297, x, y, z, o, 83, 60000)
Unit:SpawnCreature(9297, x, y, z, o, 83, 60000)
Unit:SpawnCreature(9297, x, y, z, o, 83, 60000)
Unit:SpawnCreature(9297, x, y, z, o, 83, 60000)
Unit:SpawnCreature(9297, x, y, z, o, 83, 60000)
Unit:SpawnCreature(9297, x, y, z, o, 83, 60000)
end

function TaxiOG_LeaveCombat(Unit, Event)
Unit:RemoveEvents()
end

function TaxiOG_Died(Unit, Event)
Unit:RemoveEvents()
end


RegisterUnitEvent(3310, 1, "TaxiOG_Combat")
RegisterUnitEvent(3310, 2, "TaxiOG_LeaveCombat")
RegisterUnitEvent(3310, 4, "TaxiOG_Died")

--Alliance
--Stormwind

function TaxiSW_Combat(Unit, Event)
local x = Unit:GetX()
local y = Unit:GetY()
local z = Unit:GetZ()
local o = Unit:GetO()
Unit:SpawnCreature(9526, x, y, z, o, 12, 60000)
Unit:SpawnCreature(9526, x, y, z, o, 12, 60000)
Unit:SpawnCreature(9526, x, y, z, o, 12, 60000)
Unit:SpawnCreature(9526, x, y, z, o, 12, 60000)
Unit:SpawnCreature(9526, x, y, z, o, 12, 60000)
Unit:SpawnCreature(9526, x, y, z, o, 12, 60000)
end

function TaxiSW_LeaveCombat(Unit, Event)
Unit:RemoveEvents()
end

function TaxiSW_Died(Unit, Event)
Unit:RemoveEvents()
end


RegisterUnitEvent(352, 1, "TaxiSW_Combat")
RegisterUnitEvent(352, 2, "TaxiSW_LeaveCombat")
RegisterUnitEvent(352, 4, "TaxiSW_Died")

--Darnassus

function TaxiRT_Combat(Unit, Event)
local x = Unit:GetX()
local y = Unit:GetY()
local z = Unit:GetZ()
local o = Unit:GetO()
Unit:SpawnCreature(9527, x, y, z, o, 80, 60000)
Unit:SpawnCreature(9527, x, y, z, o, 80, 60000)
Unit:SpawnCreature(9527, x, y, z, o, 80, 60000)
Unit:SpawnCreature(9527, x, y, z, o, 80, 60000)
Unit:SpawnCreature(9527, x, y, z, o, 80, 60000)
Unit:SpawnCreature(9527, x, y, z, o, 80, 60000)
end

function TaxiRT_LeaveCombat(Unit, Event)
Unit:RemoveEvents()
end

function TaxiRT_Died(Unit, Event)
Unit:RemoveEvents()
end


RegisterUnitEvent(3838, 1, "TaxiRT_Combat")
RegisterUnitEvent(3838, 2, "TaxiRT_LeaveCombat")
RegisterUnitEvent(3838, 4, "TaxiRT_Died")


--Ironforge

function TaxiIF_Combat(Unit, Event)
local x = Unit:GetX()
local y = Unit:GetY()
local z = Unit:GetZ()
local o = Unit:GetO()
Unit:SpawnCreature(9526, x, y, z, o, 55, 60000)
Unit:SpawnCreature(9526, x, y, z, o, 55, 60000)
Unit:SpawnCreature(9526, x, y, z, o, 55, 60000)
Unit:SpawnCreature(9526, x, y, z, o, 55, 60000)
Unit:SpawnCreature(9526, x, y, z, o, 55, 60000)
Unit:SpawnCreature(9526, x, y, z, o, 55, 60000)
end

function TaxiIF_LeaveCombat(Unit, Event)
Unit:RemoveEvents()
end

function TaxiIF_Died(Unit, Event)
Unit:RemoveEvents()
end


RegisterUnitEvent(1573, 1, "TaxiIF_Combat")
RegisterUnitEvent(1573, 2, "TaxiIF_LeaveCombat")
RegisterUnitEvent(1573, 4, "TaxiIF_Died")

--Exodar

function TaxiEX_Combat(Unit, Event)
local x = Unit:GetX()
local y = Unit:GetY()
local z = Unit:GetZ()
local o = Unit:GetO()
Unit:SpawnCreature(9527, x, y, z, o, 1638, 60000)
Unit:SpawnCreature(9527, x, y, z, o, 1638, 60000)
Unit:SpawnCreature(9527, x, y, z, o, 1638, 60000)
Unit:SpawnCreature(9527, x, y, z, o, 1638, 60000)
Unit:SpawnCreature(9527, x, y, z, o, 1638, 60000)
Unit:SpawnCreature(9527, x, y, z, o, 1638, 60000)
end

function TaxiEX_LeaveCombat(Unit, Event)
Unit:RemoveEvents()
end

function TaxiEX_Died(Unit, Event)
Unit:RemoveEvents()
end


RegisterUnitEvent(17555, 1, "TaxiEX_Combat")
RegisterUnitEvent(17555, 2, "TaxiEX_LeaveCombat")
RegisterUnitEvent(17555, 4, "TaxiEX_Died")