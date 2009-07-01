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

function InjuredDraenei_OnSpawn(pUnit, event)
InjuredDraeneiChance = math.random(1, 2)
if (InjuredDraeneiChance==1) then
	pUnit:SetStandState(3)
end
if (InjuredDraeneiChance==2) then
	 pUnit:SetStandState(1)
     pUnit:SetCombatCapable(0)
end
end
RegisterUnitEvent(16971, 6, "InjuredDraenei_OnSpawn")

function DraeneiSurvivor_OnSpawn(pUnit, event)
SurvivorDraeneiChance = math.random(1, 3)
if (SurvivorDraeneiChance==1) then
	pUnit:SetStandState(3)
end
if (SurvivorDraeneiChance==2) then
     pUnit:CastSpell(28630)
	 pUnit:SetStandState(1)
end
if (SurvivorDraeneiChance==3) then
     pUnit:CastSpell(28630)
     pUnit:SetCombatCapable(0)
end
end

RegisterUnitEvent(16483, 6, "DraeneiSurvivor_OnSpawn")