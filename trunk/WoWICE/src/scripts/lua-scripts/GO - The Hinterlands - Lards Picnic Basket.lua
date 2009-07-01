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

function Lards_Picnic_Basket_onUse (pUnit, Event)
	pUnit:SpawnCreature (14748, 401.681061, -4825.897949, 9.381310, 3.16951, 95, 540000)
	pUnit:SpawnCreature (14748, 403.259125, -4830.528320, 8.991310, 3.16951, 95, 540000)
	pUnit:SpawnCreature (14748, 404.802185, -4820.998535, 10.790082, 3.16951, 95, 540000)
end
RegisterGameObjectEvent (179910, 2, "Lards_Picnic_Basket_onUse")