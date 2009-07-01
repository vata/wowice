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

function Sladran_Viper_OnCombat(pUnit, Event)
pUnit:RegisterEvent("Slad'ran_Viper_Venomous_Bite", math.random(12000, 16000), 0)
end

function Sladran_Viper_OnLeaveCombat(pUnit, Event)
pUnit:RemoveEvents()
end

function Sladran_Viper_OnKillTarget(pUnit, Event)
end

function Sladran_Viper_OnDeath(pUnit, Event)
pUnit:RemoveEvents()
end

RegisterUnitEvent(29680, 1, "Sladran_Viper_OnCombat")
RegisterUnitEvent(29680, 2, "Sladran_Viper_OnLeaveCombat")
RegisterUnitEvent(29680, 3, "Sladran_Viper_OnKillTarget")
RegisterUnitEvent(29680, 4, "Sladran_Viper_OnDeath")

function Sladran_Viper_Venomous_Bite(pUnit, Event)
pUnit:FullCastSpellOnTarget(54987, pUnit:GetMainTank())
end