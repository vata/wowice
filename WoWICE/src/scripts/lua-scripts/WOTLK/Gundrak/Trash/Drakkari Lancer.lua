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

function Drakkari_Lancer_OnCombat(pUnit, Event)
pUnit:RegisterEvent("Drakkari_Lancer_Disarm", math.random(17000, 26000), 0)
pUnit:RegisterEvent("Drakkari_Lancer_Impale", math.random(13000, 16000), 0)
pUnit:RegisterEvent("Drakkari_Lancer_Retaliation", 30000, 0)
end

function Drakkari_Lancer_OnLeaveCombat(pUnit, Event)
pUnit:RemoveEvents()
end

function Drakkari_Lancer_OnKillTarget(pUnit, Event)
end

function Drakkari_Lancer_OnDeath(pUnit, Event)
pUnit:RemoveEvents()
end

RegisterUnitEvent(29819, 1, "Drakkari_Lancer_OnCombat")
RegisterUnitEvent(29819, 2, "Drakkari_Lancer_OnLeaveCombat")
RegisterUnitEvent(29819, 3, "Drakkari_Lancer_OnKillTarget")
RegisterUnitEvent(29819, 4, "Drakkari_Lancer_OnDeath")

function Drakkari_Lancer_Disarm(pUnit, Event)
pUnit:FullCastSpellOnTarget(6713, pUnit:GetMainTank())
end

function Drakkari_Lancer_Impale(pUnit, Event)
pUnit:FullCastSpellOnTarget(55622, pUnit:GetMainTank())
end

function Drakkari_Lancer_Retaliation(pUnit, Event)
pUnit:FullCastSpell(40546)
end
