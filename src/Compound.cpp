// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


#include <vector>

#include "Constants.h"
#include "Compound.h"


using std::vector;


// ----------------------------------------------------------------  default constructor

Compound::Compound (void)
        : 	GeometricObject() {}


// ---------------------------------------------------------------- clone

Compound*
Compound::clone(void) const {
    return (new Compound(*this));
}


// ---------------------------------------------------------------- copy constructor

Compound::Compound (const Compound& c)
        : GeometricObject(c) {

    copy_objects(c.objects);
}



// ---------------------------------------------------------------- assignment operator

Compound&
Compound::operator= (const Compound& rhs) {
    if (this == &rhs)
        return (*this);

    GeometricObject::operator= (rhs);

    copy_objects(rhs.objects);

    return (*this);
}


// ---------------------------------------------------------------- destructor

Compound::~Compound(void) {
    delete_objects();
}


// ---------------------------------------------------------------- add_object

void
Compound::add_object(GeometricObject* object_ptr) {
    objects.push_back(object_ptr);
}


//------------------------------------------------------------------ set_material
// sets the same material on all objects

void Compound::set_material(MaterialPtr material_ptr) {
    int num_objects = objects.size();

    for (int j = 0; j < num_objects; j++)
        objects[j]->set_material(material_ptr);
}


//------------------------------------------------------------------ delete_objects
// Deletes the objects in the objects array, and erases the array.
// The array still exists, because it'ss an automatic variable, but it's empty

void
Compound::delete_objects(void) {
    int num_objects = objects.size();

    for (int j = 0; j < num_objects; j++) {
        delete objects[j];
        objects[j] = NULL;
    }

    objects.erase(objects.begin(), objects.end());
}


//------------------------------------------------------------------ copy_objects

void
Compound::copy_objects(const vector<GeometricObject*>& rhs_ojects) {
    delete_objects();
    int num_objects = rhs_ojects.size();

    for (int j = 0; j < num_objects; j++)
        objects.push_back(rhs_ojects[j]->clone());
}


//------------------------------------------------------------------ hit

bool
Compound::hit(const Ray& ray, double& tmin, ShadeRec& sr) const {
    double		t;
    Normal		normal;
    Point3D		local_hit_point;
    bool		hit 		= false;
    tmin 		= kHugeValue;
    int 		num_objects	= objects.size();

    for (int j = 0; j < num_objects; j++)
        if (objects[j]->hit(ray, t, sr) && (t < tmin)) {
            hit				= true;
            tmin 			= t;
            material_ptr	= objects[j]->get_material();	// lhs is GeometricObject::material_ptr
            normal			= sr.normal;
            local_hit_point	= sr.local_hit_point;
        }

    if (hit) {
        sr.t				= tmin;
        sr.normal 			= normal;
        sr.local_hit_point 	= local_hit_point;
    }

    return (hit);
}


