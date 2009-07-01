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

function MechaGnome_OnGossip(pUnit, event, player, pMisc)
if (player:HasFinishedQuest(12937) == true) and (player:HasFinishedQuest(12931) == true) and (player:HasFinishedQuest(12937) == true) and (player:HasFinishedQuest(12957) == false) then
pUnit:GossipCreateMenu(100, player, 0)
pUnit:GossipMenuAddItem(0, "I´m not a laborer. I´m here to free you from servitude in the mines.", 1, 0)
pUnit:GossipSendMenu(player)
end
end

function MechaGnome_OnGossipSel(pUnit, event, player, id, intid, code, pMisc)
if (intid == 1) then
local ChatRandom = math.random(1, 4)
player:AdvanceQuestObjective(12957, 0)
pUnit:RegisterEvent("MechaGnome_Despawn", 4500, 1)
if ChatRandom == 1 then
pUnit:SendChatMessage(12, 0, "Does not compute. Unit malfunctioning. Directive: shut down.")
elseif ChatRandom == 2 then
pUnit:SendChatMessage(12, 0, "New directive: assist in the defeat of the iron dwarves.")
elseif ChatRandom == 3 then
pUnit:SendChatMessage(12, 0, "New directive: leave mine and return to Inventor's Library")
elseif ChatRandom == 4 then
pUnit:SendChatMessage(12, 0, "Thank you, I will join your struggle against the stormforged.")
end
end
end

function MechaGnome_Despawn(pUnit, event)
pUnit:Despawn(0, 0)
end

RegisterUnitGossipEvent(666667, 1, "MechaGnome_OnGossip")
RegisterUnitGossipEvent(666667, 2, "MechaGnome_OnGossipSel")