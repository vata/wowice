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

function Darrowshire_Spirit_Spawn (pUnit, Event)
	x = pUnit:GetX()
	y = pUnit:GetY()
	z = pUnit:GetZ()
	o = pUnit:GetO()
	DoSpawn = math.random (2) -- Random number, either 1 or 2
	
	if (DoSpawn == 2) then
		pUnit:SpawnCreature(11064, x, y, z, o, 35, 300000)
	end
end
RegisterUnitEvent (8530, 4, "Darrowshire_Spirit_Spawn")
RegisterUnitEvent (8531, 4, "Darrowshite_Spirit_Spawn")
RegisterUnitEvent (8532, 4, "Darrowshire_Spirit_Spawn")
