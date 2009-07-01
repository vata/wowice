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

function RottingCadaver_OnDied (pUnit, Event)
	x = pUnit:GetX ()
	y = pUnit:GetY ()
	z = pUnit:GetZ ()
	o = pUnit:GetO ()
	
	pUnit:SpawnCreature (10925, x, y, z, o, 21, 360000)
	
	x = x + 0.3
	
	pUnit:SpawnCreature (10925, x, y, z, o, 21, 360000)
end
RegisterUnitEvent (4474, 4, "RottingCadaver_OnDied")

function RottingWorm_OnSpawn (pUnit, Event)
	pUnit:SetScale (0.2)
end
RegisterUnitEvent (10925, 6, "RottingWorm_OnSpawn")

function VileSlime_OnDied (pUnit, Event)
	x = pUnit:GetX ()
	y = pUnit:GetY ()
	z = pUnit:GetZ ()
	o = pUnit:GetO ()
	
	pUnit:SpawnCreature (8257, x, y, z, o, 104, 360000)
	
	x = x - 1
	
	pUnit:SpawnCreature (8257, x, y, z, o, 104, 360000)
	
	x = x + 2
	
	pUnit:SpawnCreature (8257, x, y, z, o, 104, 360000)
end
RegisterUnitEvent (1806, 4, "VileSlime_OnDied")

function RWOO_OnLeaveCombat (pUnit, Event)
	pUnit:Despawn (1000, 0)
end
RegisterUnitEvent (10925, 2, "RWOO_OnLeaveCombat")
RegisterUnitEvent (8257, 2, "RWOO_OnLeaveCombat") 