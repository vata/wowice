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

function TeleportDown_AI(pUnit,Event)
	pUnit:RegsiterEvent("TeleportDown_DownFront", 1000, 0)
	pUnit:RegsiterEvent("TeleportDown_DownBack", 1000, 0)
end

function TeleportDown_DownFront(pUnit,Event)
 if pUnit:IsInFront() then
	pUnit:Teleport(609, 2389.989990, -5640.930176, 377.266998)
end
end

function TeleportDown_DownBack(pUnit,Event)
 if pUnit:IsInBack() then
	pUnit:Teleport(609, 2389.989990, -5640.930176, 377.266998)
end
end

RegisterUnitEvent(29581, 10, "TeleportDown_AI")

function TeleportUp_AI(pUnit,Event)
	pUnit:RegsiterEvent("TeleportDown_UpFront", 1000, 0)
	pUnit:RegsiterEvent("TeleportDown_UpBack", 1000, 0)
end

function TeleportUp_UpFront(pUnit,Event)
 if pUnit:IsInFront() then
	pUnit:Teleport(609, 2383.649902, -5645.240234, 420.880005)
end
end

function TeleportUp_UpBack(pUnit,Event)
 if pUnit:IsInBack() then
	pUnit:Teleport(609, 2383.649902, -5645.240234, 420.880005)
end
end

RegisterUnitEvent(29580, 10, "TeleportUp_AI")