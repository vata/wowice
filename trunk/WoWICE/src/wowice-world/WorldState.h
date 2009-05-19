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

#ifndef __WORLDSTATE_H
#define __WORLDSTATE_H

class WorldStateHandler;
typedef std::map<uint32, WorldStateHandler*> WorldStateHandlerMap;
typedef std::map<uint32, uint32> WorldStateMap;

class WorldStateHandler
{
public:
	WorldStateMap m_states;

	void SetState(uint32 index, uint32 value);

	WoWICE_INLINE void EraseState(uint32 index) { m_states.erase(index); }
};

#endif
