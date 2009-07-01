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

RegisterUnitEvent(17008, 18, "guldan")
RegisterUnitEvent(17008, 4, "guldan_Died")

function guldan_Died(Unit, event, player)
Unit:RemoveEvents()
end

function guldan(Unit, event, player)
Unit:RegisterEvent("guldan_Say",69000, 0)
end

function guldan_Say(Unit, event, player)
Unit:SendChatMessage(12, 0, "Behold those who have power, and who are not afraid to wield it. Behold... the warlocks!")
end