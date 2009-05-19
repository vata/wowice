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

#ifndef G3D_SPHERE_H
#define G3D_SPHERE_H

#include "G3D/platform.h"
#include "G3D/Vector3.h"
#include "G3D/Array.h"
#include "G3D/Sphere.h"

namespace G3D {

/**
 Sphere.
 */
class Sphere {
private:

    static int32     dummy;

public:
    Vector3          center;
    float            radius;

    Sphere() {
        center = Vector3::zero();
        radius = 0;
    }

    Sphere(
        const Vector3&  center,
        float           radius) {

        this->center = center;
        this->radius = radius;
    }

    virtual ~Sphere() {}

    bool operator==(const Sphere& other) const {
        return (center == other.center) && (radius == other.radius);
    }

    bool operator!=(const Sphere& other) const {
        return !((center == other.center) && (radius == other.radius));
    }

    /**
     Returns true if point is less than or equal to radius away from
     the center.
     */
    bool contains(const Vector3& point) const;

/**
	 @deprecated Use culledBy(Array<Plane>&)
     */
    bool culledBy(
        const class Plane*  plane,
        int                 numPlanes,
		int32&				cullingPlaneIndex,
		const uint32  		testMask,
        uint32&             childMask) const;

    /**
	 @deprecated Use culledBy(Array<Plane>&)
     */
    bool culledBy(
        const class Plane*  plane,
        int                 numPlanes,
		int32&				cullingPlaneIndex = dummy,
		const uint32  		testMask = -1) const;

	/**
      See AABox::culledBy
	 */
	bool culledBy(
		const Array<Plane>&		plane,
		int32&					cullingPlaneIndex,
		const uint32  			testMask,
        uint32&                 childMask) const;

    /**
     Conservative culling test that does not produce a mask for children.
     */
	bool culledBy(
		const Array<Plane>&		plane,
		int32&					cullingPlaneIndex = dummy,
		const uint32  			testMask		  = -1) const;
    virtual std::string toString() const;

    float volume() const;

    /** @deprecated */
    float surfaceArea() const;

    inline float area() const {
        return surfaceArea();
    }

    /**
     Uniformly distributed on the surface.
     */
    Vector3 randomSurfacePoint() const;

    /**
     Uniformly distributed on the interior (includes surface)
     */
    Vector3 randomInteriorPoint() const;

    void getBounds(class AABox& out) const;
};

} // namespace

inline size_t hashCode(const G3D::Sphere& sphere) {
    return (size_t)(hashCode(sphere.center) + (sphere.radius * 13));
}

#endif
