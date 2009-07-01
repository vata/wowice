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

--Rewrite: Recon
function Pandemonius_OnCombat(pUnit, Event)
	pUnit:RegisterEvent("speak",2, 1)
	pUnit:RegisterEvent("Pandemonius_Void_Blast",5000, 0)
	pUnit:RegisterEvent("Pandemonius_Dark_Shell",17000, 0) --i dont know how often :S
end

function speak(pUnit, Event)
	local eselyke = math.random(1,3)
	if(eselyke == 1) then
	pUnit:PlaySoundToSet(10561)
	pUnit:SendChatMessage(11, 0, "I will feed on your soul.")
	end
	if(eselyke == 2) then
	pUnit:PlaySoundToSet(10562)
	pUnit:SendChatMessage(11, 0, "So... full of life!")
	end
	if(eselyke == 3) then
	pUnit:PlaySoundToSet(10563)
	pUnit:SendChatMessage(11, 0, "Do not... resist.")
	end	
end

function Pandemonius_Void_Blast(pUnit, event, miscpUnit, misc)
	print "Pandemonius Void Blast"
	pUnit:FullCastSpellOnTarget(32325,pUnit:GetClosestPlayer(0))

end

function Pandemonius_Dark_Shell(pUnit, event, miscpUnit, misc)
	print "Pandemonius Dark Shell"
	pUnit:CastSpell(32358)
end

function Pandemonius_OnKilledTarget (pUnit, Event)
	local eselly = math.random(1,2)
	if(eselly == 1) then
	pUnit:PlaySoundToSet(10565)
	pUnit:SendChatMessage(11, 0, "More... I must have more!")
	end
	if(eselly == 2) then
	pUnit:PlaySoundToSet(10564)
	pUnit:SendChatMessage(11, 0, "Yes! I am... empowered!")
	end
end

function Pandemonius_OnLeaveCombat(pUnit, Event)
	pUnit:RemoveEvents()	
end


function Pandemonius_OnDied(pUnit, event, player)
pUnit:PlaySoundToSet(10566)
pUnit:SendChatMessage(11, 0, "To the void... once... more.")
pUnit:RemoveEvents()
end

RegisterUnitEvent(18341, 1, "Pandemonius_OnCombat")
RegisterUnitEvent(18341, 2, "Pandemonius_OnLeaveCombat")
RegisterUnitEvent(18341, 3, "Pandemonius_OnKilledTarget")
RegisterUnitEvent(18341, 4, "Pandemonius_OnDied")
