#ifndef __RAY_CAST__
#define __RAY_CAST__


// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


#include "Tracer.h"

class RayCast: public Tracer {
public:
    RayCast(WorldPtr _worldPtr);

    virtual ~RayCast();
    virtual RGBColor trace_ray(const Ray ray, const int depth) const;

private:
    RayCast();
};

#endif
