// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


#include "Whitted.h"
#include "World.h"
#include "ShadeRec.h"
#include "Material.h"


Whitted::Whitted(WorldPtr _worldPtr): Tracer(_worldPtr) {}
Whitted::~Whitted() {}


RGBColor Whitted::trace_ray(const Ray ray, const int depth) const {
    return BLACK;
    /*
    	if (depth > world_ptr->vp.max_depth)
    		return(black);
    	else {
    		ShadeRec sr(world_ptr->hit_objects(ray));

    		if (sr.hit_an_object) {
    			sr.depth = depth;
    			sr.ray = ray;
    			return (sr.material_ptr->shade(sr));
    		}
    		else
    			return (world_ptr->background_color);
    	}
    */
}
