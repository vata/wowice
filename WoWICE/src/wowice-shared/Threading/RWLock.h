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

#ifndef RWLOCK_H
#define RWLOCK_H

#include "Mutex.h"

class RWLock
{
public: 
	WoWICE_INLINE void AcquireReadLock()
	{
		_lock.Acquire();
	}
	
	WoWICE_INLINE void ReleaseReadLock()
	{
		_lock.Release();
	}

	WoWICE_INLINE void AcquireWriteLock()
	{
		_lock.Acquire();
	}

	WoWICE_INLINE void ReleaseWriteLock()
	{
		_lock.Release();
	}
  
private:
	Mutex _lock;
}; 

#endif
