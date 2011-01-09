#ifndef __MULTIPLE_OBJECTS__
#define __MULTIPLE_OBJECTS__


// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


#include "Tracer.h"

class MultipleObjects: public Tracer {
public:
    MultipleObjects(WorldPtr _world_ptr);

    virtual ~MultipleObjects() {}

    virtual RGBColor trace_ray(const Ray& ray) const;

private:
    MultipleObjects();

};

#endif

