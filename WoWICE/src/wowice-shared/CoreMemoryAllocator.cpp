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

#include <new>

#ifdef WIN32
#ifdef SCRIPTLIB

__declspec(dllimport) void* AllocateMemory(size_t iSize);
__declspec(dllimport) void FreeMemory(void* pPointer);

void * ::operator new(size_t iSize)
{
	return AllocateMemory(iSize);
}

void ::operator delete(void* pPointer)
{
	FreeMemory(pPointer);
}

#endif		// SCRIPTLIB
#endif		// WIN32

