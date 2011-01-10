// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


#include "Tracer.h"


Tracer::Tracer(WorldPtr _worldPtr): world_ptr(_worldPtr) {}
Tracer::~Tracer() {}

RGBColor Tracer::trace_ray(const Ray& ray) const {
    return BLACK;
}

RGBColor Tracer::trace_ray(const Ray ray, const int depth) const {
    return BLACK;
}




