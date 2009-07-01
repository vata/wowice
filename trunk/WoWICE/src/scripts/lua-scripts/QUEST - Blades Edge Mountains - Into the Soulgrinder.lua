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

function Into_the_Soulgrinder_Quest_onComplete (pUnit, Event)
	pUnit:SpawnCreature (23053, 2794.978271, 5842.185547, 35.911819, 3.61522, 35, 540000)
end

--RegisterQuestEvent(11000, 1, "IntotheSoulgrinder_OnQuestComplete") <<<<<<<<<<<<<<<<<<<< Needs Ascent Functionality