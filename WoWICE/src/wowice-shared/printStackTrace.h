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
 
#ifndef _PRINTSTACKTRACE_H
#define _PRINTSTACKTRACE_H

/**
 * Prints formatted call stack to the user defined buffer,
 * always terminating the buffer with 0.
 * Uses stack frame to find out the caller function address and 
 * the map file to find out the function name.
 */
extern SERVER_DECL void printStackTrace( char* buffer, int bufferSize );
extern SERVER_DECL void printStackTrace( );
extern SERVER_DECL void arcAssertFailed( const char* fname, int line, const char* expr );

#endif // _PRINTSTACKTRACE_H
