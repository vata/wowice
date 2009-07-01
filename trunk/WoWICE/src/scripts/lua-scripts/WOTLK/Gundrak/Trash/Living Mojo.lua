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
 
-- Scripted By:  n4xD

function Living_Mojo_OnCombat(pUnit, Event)
pUnit:RegisterEvent("Living_Mojo_Mojo_Puddle", math.random(20000, 23000), 0)
pUnit:RegisterEvent("Living_Mojo_Mojo_Wave", math.random(27000, 29000), 0)
end

function Living_Mojo_OnLeaveCombat(pUnit, Event)
pUnit:RemoveEvents()
end

function Living_Mojo_OnKillTarget(pUnit, Event)
end

function Living_Mojo_OnDeath(pUnit, Event)
pUnit:RemoveEvents()
end

RegisterUnitEvent(29830, 1, "Living_Mojo_OnCombat")
RegisterUnitEvent(29830, 2, "Living_Mojo_OnLeaveCombat")
RegisterUnitEvent(29830, 3, "Living_Mojo_OnKillTarget")
RegisterUnitEvent(29830, 4, "Living_Mojo_OnDeath")

function Living_Mojo_Mojo_Puddle(pUnit, Event)
pUnit:FullCastSpell(55627)
end

function Living_Mojo_Mojo_Wave(pUnit, Event)
pUnit:FullCastSpellOnTarget(55626, pUnit:GetRandomPlayer(0))
end
