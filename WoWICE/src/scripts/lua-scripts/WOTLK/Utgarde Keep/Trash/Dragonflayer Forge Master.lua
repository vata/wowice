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

function Dragonflayer_Forge_Master_OnCombat(pUnit, Event)
pUnit:RegisterEvent("Dragonflayer_Forge_Master_Burning_Brand", math.random(7000, 12000), 0)
end

function Dragonflayer_Forge_Master_OnLeaveCombat(pUnit, Event)
pUnit:RemoveEvents()
end

function Dragonflayer_Forge_Master_OnDeath(pUnit, Event)
pUnit:RemoveEvents()
end

RegisterUnitEvent(24079, 1, "Dragonflayer_Forge_Master_OnCombat")
RegisterUnitEvent(24079, 2, "Dragonflayer_Forge_Master_OnLeaveCombat")
RegisterUnitEvent(24079, 4, "Dragonflayer_Forge_Master_OnDeath")

function Dragonflayer_Forge_Master_Burning_Brand(pUnit, Event)
pUnit:FullCastSpell(43757)
end
