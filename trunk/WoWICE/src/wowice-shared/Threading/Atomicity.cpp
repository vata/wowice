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

#include "../Common.h"

namespace Wowice{
	namespace Threading{


		void AtomicCounter::SetVal( unsigned long val ){
#ifdef WIN32
			InterlockedExchange( reinterpret_cast< volatile LONG* >( &counter ), LONG( val ) );
#else
#ifdef __GNUC__
			__sync_val_compare_and_swap( &counter, counter, val );
#else
#error Your platform (architecture and compiler) is NOT supported. Wowice requires little endian architecture, and at least GCC 4.1
#endif
#endif
		}


		unsigned long AtomicCounter::operator++(){
			unsigned long val = 0;

#ifdef WIN32
			val = InterlockedIncrement( reinterpret_cast< volatile LONG* >( &counter ) );
#else
#ifdef __GNUC__
			val = __sync_add_and_fetch( &counter, 1 );
#else
#error Your platform (architecture and compiler) is NOT supported. Wowice requires little endian architecture, and at least GCC 4.1
#endif
#endif

			return val;
		}

		unsigned long AtomicCounter::operator--(){
			unsigned long val = 0;

#ifdef WIN32
			val = InterlockedDecrement( reinterpret_cast< volatile LONG* >( &counter ) );
#else
#ifdef __GNUC__
			val = __sync_add_and_fetch( &counter, -1 );
#else
#error Your platform (architecture and compiler) is NOT supported. Wowice requires little endian architecture, and at least GCC 4.1
#endif
#endif
			return val;
		}
	}
}
