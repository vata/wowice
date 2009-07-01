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

function Drakkari_Golem_OnCombat(pUnit, Event)
pUnit:RegisterEvent("Drakkari_Golem_Body_of_Stone", math.random(45000, 49000), 0)
pUnit:RegisterEvent("Drakkari_Golem_Shockwave", math.random(17000, 24000), 0)
pUnit:RegisterEvent("Drakkari_Golem_Thunderclap", math.random(13000, 16000), 0)
end

function Drakkari_Golem_OnLeaveCombat(pUnit, Event)
pUnit:RemoveEvents()
end

function Drakkari_Golem_OnKillTarget(pUnit, Event)
end

function Drakkari_Golem_OnDeath(pUnit, Event)
pUnit:RemoveEvents()
end

RegisterUnitEvent(29832, 1, "Drakkari_Golem_OnCombat")
RegisterUnitEvent(29832, 2, "Drakkari_Golem_OnLeaveCombat")
RegisterUnitEvent(29832, 3, "Drakkari_Golem_OnKillTarget")
RegisterUnitEvent(29832, 4, "Drakkari_Golem_OnDeath")

function Drakkari_Golem_Body_of_Stone(pUnit, Event)
pUnit:FullCastSpell(55633)
end

function Drakkari_Golem_Shockwave(pUnit, Event)
pUnit:FullCastSpell(55636)
end

function Drakkari_Golem_Thunderclap(pUnit, Event)
pUnit:FullCastSpell(55635)
end
