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

function Drakkari_Fire_Weaver_OnCombat(pUnit, Event)
pUnit:RegisterEvent("Drakkari_Fire_Weaver_Blast_Wave", math.random(19000, 23000), 0)
pUnit:RegisterEvent("Drakkari_Fire_Weaver_Lava_Burst", math.random(25000, 27000), 0)
pUnit:RegisterEvent("Drakkari_Fire_Weaver_Flame_Shock", math.random(12000, 14000), 0)
end

function Drakkari_Fire_Weaver_OnLeaveCombat(pUnit, Event)
pUnit:RemoveEvents()
end

function Drakkari_Fire_Weaver_OnKillTarget(pUnit, Event)
end

function Drakkari_Fire_Weaver_OnDeath(pUnit, Event)
pUnit:RemoveEvents()
end

RegisterUnitEvent(29822, 1, "Drakkari_Fire_Weaver_OnCombat")
RegisterUnitEvent(29822, 2, "Drakkari_Fire_Weaver_OnLeaveCombat")
RegisterUnitEvent(29822, 3, "Drakkari_Fire_Weaver_OnKillTarget")
RegisterUnitEvent(29822, 4, "Drakkari_Fire_Weaver_OnDeath")

function Drakkari_Fire_Weaver_Blast_Wave(pUnit, Event)
pUnit:FullCastSpell(15744)
end

function Drakkari_Fire_Weaver_Lava_Burst(pUnit, Event)
pUnit:FullCastSpellOnTarget(55659, pUnit:GetRandomPlayer(0))
end

function Drakkari_Fire_Weaver_Flame_Shock(pUnit, Event)
pUnit:FullCastSpellOnTarget(55613, pUnit:GetRandomPlayer(0))
end
