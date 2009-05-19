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

#ifndef G3D_FORMAT_H
#define G3D_FORMAT_H

#include "G3D/platform.h"
#include <string>
#include <stdio.h>
#include <cstdarg>
#include <assert.h>
#ifndef G3D_WIN32
    // Don't include varargs.h for some random
    // gcc reason
    //#include <varargs.h>
    #include <stdarg.h>
#endif

#ifndef _MSC_VER
    #ifndef __cdecl
        #define __cdecl __attribute__((cdecl))
    #endif
#endif

namespace G3D {

/**
  Produces a string from arguments of the style of printf.  This avoids
  problems with buffer overflows when using sprintf and makes it easy
  to use the result functionally.  This function is fast when the resulting
  string is under 160 characters (not including terminator) and slower
  when the string is longer.
 */
std::string format(
    const char*                 fmt
    ...) G3D_CHECK_PRINTF_ARGS;

/**
  Like format, but can be called with the argument list from a ... function.
 */
std::string vformat(
    const char*                 fmt,
    va_list                     argPtr) G3D_CHECK_VPRINTF_ARGS;


}; // namespace

#endif
