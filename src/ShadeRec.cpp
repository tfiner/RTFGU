// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


// This file contains the definition of the class ShadeRec

// There is no default constructor as the World reference has to be initialised
// There is also no assignment operator as we don't want to assign the world anywhere
// The copy constructor only copies the world reference
// The ray tracer is written so that new ShadeRec objects are always constructed
// using the first constructor or the copy constructor

#include "Constants.h"
#include "ShadeRec.h"

// ------------------------------------------------------------------ constructor

ShadeRec::ShadeRec(World& wr)
	: 	hit_an_object(false),
		material_ptr(NULL),
		hit_point(),
		local_hit_point(),
		normal(),
		ray(),
		depth(0),
		color(black),
		t(0.0),
		u(0.0),
		v(0.0),
		w(wr)
{}


// ------------------------------------------------------------------ copy constructor

ShadeRec::ShadeRec(const ShadeRec& sr)
	: 	hit_an_object(sr.hit_an_object),
		material_ptr(sr.material_ptr),
		hit_point(sr.hit_point),
		local_hit_point(sr.local_hit_point),
		normal(sr.normal),
		ray(sr.ray),
		depth(sr.depth),
		color(sr.color),
		t(sr.t),
		u(sr.u),
		v(sr.v),
		w(sr.w)
{}


// ------------------------------------------------------------------ destructor

ShadeRec::~ShadeRec(void) {
	if (material_ptr) {
		delete material_ptr;
		material_ptr = NULL;
	}
}
		
		
						
		
