// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


#include "RayCast.h"
#include "World.h"
#include "ShadeRec.h"
#include "Material.h"

RayCast::RayCast(WorldPtr _worldPtr): Tracer(_worldPtr) {}
RayCast::~RayCast() {}

// this ignores the depth argument

RGBColor RayCast::trace_ray(const Ray ray, const int depth) const {
    ShadeRec sr(world_ptr->hit_objects(ray));

    if (sr.hit_an_object) {
        sr.ray = ray;			// used for specular shading
        return (sr.material_ptr->shade(sr));
    }

    return world_ptr->get_background();
}


