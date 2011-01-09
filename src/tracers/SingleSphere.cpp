// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


#include "SingleSphere.h"
#include "World.h"
#include "ShadeRec.h"



SingleSphere::SingleSphere(WorldPtr _worldPtr): Tracer(_worldPtr) {}
SingleSphere::~SingleSphere() {}


RGBColor SingleSphere::trace_ray(const Ray& ray) const {
    ShadeRec	sr(*world_ptr); 	// not used
    double    	t;  				// not used

    if (world_ptr->get_sphere().hit(ray, t, sr))
        return (red);
    else
        return (black);
}



