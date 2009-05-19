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

#ifndef VECTOR2INT16_H
#define VECTOR2INT16_H

#include "G3D/platform.h"
#include "G3D/g3dmath.h"

namespace G3D {

/**
 A Vector2 that packs its fields into uint16s.
 */
#ifdef G3D_WIN32
    // Switch to tight alignment
    #pragma pack(push, 2)
#endif

class Vector2int16 {
private:
    // Hidden operators
    bool operator<(const Vector2int16&) const;
    bool operator>(const Vector2int16&) const;
    bool operator<=(const Vector2int16&) const;
    bool operator>=(const Vector2int16&) const;

public:
    G3D::int16              x;
    G3D::int16              y;

    Vector2int16() : x(0), y(0) {}
    Vector2int16(G3D::int16 _x, G3D::int16 _y) : x(_x), y(_y){}
    Vector2int16(const class Vector2& v);

    inline G3D::int16& operator[] (int i) {
        debugAssert(((unsigned int)i) <= 1);
        return ((G3D::int16*)this)[i];
    }

    inline const G3D::int16& operator[] (int i) const {
        debugAssert(((unsigned int)i) <= 1);
        return ((G3D::int16*)this)[i];
    }


    inline bool operator== (const Vector2int16& rkVector) const {
        return ((int32*)this)[0] == ((int32*)&rkVector)[0];
    }

    inline bool operator!= (const Vector2int16& rkVector) const {
        return ((int32*)this)[0] != ((int32*)&rkVector)[0];
    }

}
#if defined(G3D_LINUX) || defined(G3D_OSX)
    __attribute((aligned(1)))
#endif
;

#ifdef G3D_WIN32
    #pragma pack(pop)
#endif

}
#endif
