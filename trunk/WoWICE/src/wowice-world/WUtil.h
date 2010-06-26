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

#ifndef ARCWORLDUTILS__H
#define ARCWORLDUTILS__H

namespace WoWICE{
	
	// Common WoWICE world stuff
    class Util{
    public:
        SERVER_DECL static uint32 GUID_LOPART( uint64 GUID );
        SERVER_DECL static uint32 GUID_HIPART( uint64 GUID );
		static void WOWICE_ASSERT(   bool condition );
		static uint64 MAKE_PET_GUID( uint32 entry, uint32 lowGUID );
		static uint64 MAKE_ITEM_GUID( uint32 lowGUID );
    };
}


#endif
