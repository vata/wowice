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

#ifndef G3D_REGISTRYUTIL_H
#define G3D_REGISTRYUTIL_H

#include "G3D/platform.h"
#include "G3D/g3dmath.h"

// This file is only used on Windows
#ifdef G3D_WIN32

#include <string>

namespace G3D {

/** 
    Provides generalized Windows registry querying.

    All key names are one string in the format:
        "[base key]\[sub-keys]\value"

    [base key] can be any of the following:
        HKEY_CLASSES_ROOT
        HKEY_CURRENT_CONFIG
        HKEY_CURRENT_USER
        HKEY_LOCAL_MACHINE
        HKEY_PERFORMANCE_DATA
        HKEY_PERFORMANCE_NLSTEXT
        HKEY_PERFORMANCE_TEXT
        HKEY_USERS

    keyExists() should be used to validate a key before reading or writing
    to ensure that a debug assert or false return is for a different error.
*/
class RegistryUtil {

public:
    /** returns true if the key exists */
    static bool keyExists(const std::string& key);

    /** returns false if the key could not be read for any reason. */
    static bool readInt32(const std::string& key, int32& valueData);

    /** 
      Reads an arbitrary amount of data from a binary registry key.
      returns false if the key could not be read for any reason.
    
      @beta
      @param valueData pointer to the output buffer of sufficient size. Pass NULL as valueData in order to have available data size returned in dataSize.
      @param dataSize size of the output buffer.  When NULL is passed for valueData, contains the size of available data on successful return.
    */
    static bool readBytes(const std::string& key, uint8* valueData, uint32& dataSize);

    /** returns false if the key could not be read for any reason. */
    static bool readString(const std::string& key, std::string& valueData);

    /** returns false if the key could not be written for any reason. */
    static bool writeInt32(const std::string& key, int32 valueData);

    /** 
      Writes an arbitrary amount of data to a binary registry key.
      returns false if the key could not be written for any reason.
    
      @param valueData pointer to the input buffer
      @param dataSize size of the input buffer that should be written
    */
    static bool writeBytes(const std::string& key, const uint8* valueData, uint32 dataSize);

    /** returns false if the key could not be written for any reason. */
    static bool writeString(const std::string& key, const std::string& valueData);

};

} // namespace G3D

#endif // G3D_WIN32

#endif // G3D_REGISTRYTUIL_H