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

#ifndef ATOMICITY_HPP
#define ATOMICITY_HPP

namespace Wowice{
	namespace Threading{

///////////////////////////////////////////////////////////////////////////////////////////////
//AtomicCounter class
//
//Simple and fast value container with lockless threadsafe increment and decrement operations
//
//////////////////////////////////////////////////////////////////////////////////////////////
		class AtomicCounter{

		public:
			AtomicCounter(){ counter = 0; }
			AtomicCounter( unsigned long val ){ counter = val; }

			////////////////////////////////////////////////////////////
			//void SetVal( unsigned long val )
			// lockless threadsafe set operation on the contained value
			//
			// Parameters
			//  unsigned long val  -  value to be set
			//
			// Return values
			//  None
			///////////////////////////////////////////////////////////
			void SetVal( unsigned long val );

			///////////////////////////////////////////////////////////
			//unsigned long GetVal()
			// non-threadsafe get operation on the contained value
			//
			// Parameters
			//  None
			//
			// Return values
			//  Returns the value contained
			//////////////////////////////////////////////////////////
			unsigned long GetVal(){ return counter; }


			//////////////////////////////////////////////////////////
			//unsigned long operator++()
			// lockless threadsafe prefix increment operator
			//
			// Parameters
			//  None
			//
			// Return values
			//  Returns the incremented value
			/////////////////////////////////////////////////////////
			unsigned long operator++();



			/////////////////////////////////////////////////////////
			//unsigned long operator--()
			// lockless threadsafe prefix decrement operator
			//
			// Parameters
			//  None
			//
			// Return values
			//  Returns the decremented value
			////////////////////////////////////////////////////////
			unsigned long operator--();

		private:
			AtomicCounter( AtomicCounter &other ){}
			AtomicCounter& operator=( AtomicCounter &other ){ return *this; }



#ifdef WIN32
			__declspec( align( 4 ) )  volatile unsigned long counter;
#else
			volatile unsigned long counter;
#endif
			
		};
	}
}

#endif
