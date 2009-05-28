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

#ifndef __STDAFX_H
#define __STDAFX_H

// Windows Header Files:
#include <windows.h>
#include <string>

#ifdef WIN32
	#ifndef SCRIPTLIB
		#define SERVER_DECL __declspec(dllexport)
		#define SCRIPT_DECL __declspec(dllimport)
	#else
		#define SERVER_DECL __declspec(dllimport)
		#define SCRIPT_DECL __declspec(dllexport)
	#endif
#else
	#define SERVER_DECL 
	#define SCRIPT_DECL 
#endif

#ifdef WIN32
#define ARCEMU_INLINE __forceinline
#else
#define ARCEMU_INLINE inline
#endif

typedef signed __int64 int64;
typedef signed __int32 int32;
typedef signed __int16 int16;
typedef signed __int8 int8;

typedef unsigned __int64 uint64;
typedef unsigned __int32 uint32;
typedef unsigned __int16 uint16;
typedef unsigned __int8 uint8;
#define assert(exp)     ((void)0)
#define snprintf _snprintf
#include "math.h"
#include "CellHandler.h"
#include "TerrainMgr.h"
#include "CollideInterface.h"
#include "LocationVector.h"
#include "conio.h"

#define MAXINT (1<<31)
#define COLLISION 1
#define vMapPath "./maps/"
#define ColvMapPath "./vmaps/"
#define vMapOutPath "./maps_out" //no trailing slash requirred
//#define USE_MEMORY_MAPPING_FOR_MAPS

#endif