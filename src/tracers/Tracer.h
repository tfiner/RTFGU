// This is the declaration of the base class Tracer
// The tracer classes have no copy constructor, assignment operator. or clone function because
// of the world pointer, which should not be assigned or copy constructed
// See comments in the World.h file.

#ifndef __TRACER__
#define __TRACER__


// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


#include "Constants.h"
#include "Ray.h"
#include "RGBColor.h"

#include <boost/shared_ptr.hpp>

class World;
typedef boost::shared_ptr<World> WorldPtr;


class Tracer {
public:
    Tracer(WorldPtr _world_ptr);

    virtual ~Tracer();

    virtual RGBColor trace_ray(const Ray& ray) const;
    virtual RGBColor trace_ray(const Ray ray, const int depth) const;

protected:
    WorldPtr world_ptr;

private:
    Tracer();
};

#endif

