#ifndef __BEVELED_BOX__
#define __BEVELED_BOX__

// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.



// This file contains the declaration of the class BeveledBox
// This is an axis aligned box with beleveling
// The parameters are the opposite corners and the bevel radius
// Hit functions are defined that test if the ray hits the bounding box

#include "Compound.h"
#include "Point3D.h"
#include "BBox.h"

class BeveledBox: public Compound {
	public:
		
		BeveledBox(void);   								
								
		BeveledBox(	const Point3D& 	min_corner, 
					const Point3D& 	max_corner,
					const double 	bevel_radius);
						
		BeveledBox(const BeveledBox& bb); 		
		
		virtual BeveledBox* 								
		clone(void) const;

		virtual BeveledBox& 								
		operator= (const BeveledBox& rhs);		
		
		virtual 											
		~BeveledBox(void);  
		
		virtual BBox 
		get_bounding_box(void);
				
		virtual bool												
		shadow_hit(const Ray& ray, double& tmin) const;
		
		virtual bool 																						 
		hit(const Ray& ray, double& tmin, ShadeRec& sr) const;
		
	private:
	
		Point3D		p0; 	// minimum coordinate corner
		Point3D 	p1;		// maximum coordinate corner
		double		rb;		// bevel radius
		BBox		bbox;	// bounding box
};

#endif
