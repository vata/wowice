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

function Drakkari_Earthshaker_OnCombat(pUnit, Event)
pUnit:RegisterEvent("Drakkari_Earthshaker_Head_Crack", math.random(27000, 29000), 0)
pUnit:RegisterEvent("Drakkari_Earthshaker_Powerful_Blow", math.random(17000, 18000), 0)
pUnit:RegisterEvent("Drakkari_Earthshaker_Slam_Ground", 33000, 0)
end

function Drakkari_Earthshaker_OnLeaveCombat(pUnit, Event)
pUnit:RemoveEvents()
end

function Drakkari_Earthshaker_OnKillTarget(pUnit, Event)
end

function Drakkari_Earthshaker_OnDeath(pUnit, Event)
pUnit:RemoveEvents()
end

RegisterUnitEvent(29829, 1, "Drakkari_Earthshaker_OnCombat")
RegisterUnitEvent(29829, 2, "Drakkari_Earthshaker_OnLeaveCombat")
RegisterUnitEvent(29829, 3, "Drakkari_Earthshaker_OnKillTarget")
RegisterUnitEvent(29829, 4, "Drakkari_Earthshaker_OnDeath")

function Drakkari_Earthshaker_Head_Crack(pUnit, Event)
pUnit:FullCastSpellOnTarget(16172, pUnit:GetMainTank())
end

function Drakkari_Earthshaker_Powerful_Blow(pUnit, Event)
pUnit:FullCastSpellOnTarget(55567, pUnit:GetMainTank())
end

function Drakkari_Earthshaker_Slam_Ground(pUnit, Event)
pUnit:FullCastSpell(55563)
end
