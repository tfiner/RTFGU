#ifndef __SHADE_REC__
#define __SHADE_REC__


// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


// We can use forward references for Material and World because they are a pointer and a reference

class Material;
class World;

// We need the following as #includes instead of forward class declarations,
// because we have the objects themselves, not pointers or references to them

#include "Point3D.h"
#include "Normal.h"
#include "Ray.h"
#include "RGBColor.h"

class ShadeRec {
	public:
	
		bool				hit_an_object;		// did the ray hit an object?
		Material* 			material_ptr;		// pointer to the nearest object's material
		Point3D 			hit_point;			// world coordinates of intersection
		Point3D				local_hit_point;	// world coordinates of hit point on untransformed object (used for texture transformations)
		Normal				normal;				// normal at hit point
		Ray					ray;				// required for specular highlights and area lights
		int					depth;				// recursion depth
		RGBColor			color;				// used in the Chapter 3 only
		double				t;					// ray parameter
		float				u;					// texture coordinate
		float				v;					// texture coordinate
		World&				w;					// world reference
				
		ShadeRec(World& wr);					// constructor
		ShadeRec(const ShadeRec& sr);			// copy constructor
		~ShadeRec(void);						// destructor
};

#endif
