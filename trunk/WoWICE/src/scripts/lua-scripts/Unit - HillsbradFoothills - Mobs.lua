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
-- [[ Unit - HillsbradFoothills - Mobs ]] --

function Rousch_FriendsTribute(pUnit, event)
    pUnit:Emote(113)
end

function Rousch_OnSpawn(pUnit, event)
     pUnit:SetStandState(8)
	 pUnit:RegisterEvent("Rousch_FriendsTribute",5000, 0)
	 pUnit:RemoveEvents()
end

RegisterUnitEvent(16090, 6, "Rousch_OnSpawn")