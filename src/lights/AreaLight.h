#ifndef __AREA_LIGHT__
#define __AREA_LIGHT__

// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


#include "RGBColor.h"
#include "Vector3D.h"
#include "Point3D.h"
#include "Normal.h"
#include "Light.h"
#include "Material.h"
#include "GeometricObject.h"


class AreaLight: public Light {
public:

    AreaLight();

    AreaLight(const AreaLight& al);

    virtual Light* clone() const;

    virtual ~AreaLight();

    AreaLight&
    operator= (const AreaLight& rhs);

    void
    set_object(GeometricObject* obj_ptr);

    virtual Vector3D
    get_direction(ShadeRec& s);

    virtual RGBColor
    L(ShadeRec& sr);

    virtual bool
    in_shadow(const Ray& ray, const ShadeRec& sr) const;

    virtual float
    G(const ShadeRec& sr) const;

    virtual float
    pdf(const ShadeRec& sr) const;

private:
    GeometricObject* 	object_ptr;
    MaterialPtr 		material_ptr;	 // will be an emissive material
    Point3D				sample_point;
    Normal				light_normal;    // assigned in get_direction - which therefore can't be const for any light
    Vector3D			wi;			     // unit direction from hit point being shaded to sample point on light surface

};


// --------------------------------------------------------------- set_object

inline void AreaLight::set_object(GeometricObject* obj_ptr) {
    object_ptr = obj_ptr;
    material_ptr = object_ptr->get_material();
}

#endif
