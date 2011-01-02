#ifndef __SINGLE_SPHERE__
#define __SINGLE_SPHERE__


// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


#include "Tracer.h"

class SingleSphere: public Tracer {
public:
    SingleSphere(WorldPtr _worldPtr);

    virtual ~SingleSphere();

    virtual RGBColor trace_ray(const Ray& ray) const;

private:
    SingleSphere();
};

#endif

