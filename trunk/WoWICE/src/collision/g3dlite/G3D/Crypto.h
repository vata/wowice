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

#ifndef G3D_CRYPTO_H
#define G3D_CRYPTO_H

#include "G3D/platform.h"
#include "G3D/g3dmath.h"
#include <string>

namespace G3D {

/** Cryptography and hashing helper functions */
class Crypto {
public:

    /**
     Computes the CRC32 value of a byte array.  CRC32 is designed to be a hash
     function that produces different values for similar strings.

     This implementation is compatible with PKZIP and GZIP.

     Based on http://www.gamedev.net/reference/programming/features/crc32/
    */
    static uint32 crc32(const void* bytes, size_t numBytes);

    /**
     Returns the nth prime less than 2000 in constant time.  The first prime has index
     0 and is the number 2.
     */
    static int smallPrime(int n);

    /** Returns 1 + the largest value that can be passed to smallPrime. */
    static int numSmallPrimes();
};

}

#endif
