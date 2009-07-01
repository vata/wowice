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

function Savage_Worg_OnCombat(pUnit, Event)
pUnit:RegisterEvent("Savage_Worg_Pounce", 31000, 0)
end

function Savage_Worg_OnLeaveCombat(pUnit, Event)
pUnit:RemoveEvents()
end

function Savage_Worg_OnDeath(pUnit, Event)
pUnit:RemoveEvents()
end

RegisterUnitEvent(29735, 1, "Savage_Worg_OnCombat")
RegisterUnitEvent(29735, 2, "Savage_Worg_OnLeaveCombat")
RegisterUnitEvent(29735, 4, "Savage_Worg_OnDeath")

function Savage_Worg_Pounce(pUnit, Event)
pUnit:FullCastSpellOnTarget(55077, pUnit:GetMainTank())
end
