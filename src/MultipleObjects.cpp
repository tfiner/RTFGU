// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


#include "MultipleObjects.h"
#include "World.h"

MultipleObjects::MultipleObjects(WorldPtr _worldPtr): Tracer(_worldPtr) {}

RGBColor MultipleObjects::trace_ray(const Ray& ray) const {
    ShadeRec sr(world_ptr->hit_bare_bones_objects(ray)); // sr is copy constructed
//    ShadeRec sr(world_ptr->hit_objects(ray)); // sr is copy constructed

    if (sr.hit_an_object)
        return sr.color;

    return world_ptr->get_background();
}


