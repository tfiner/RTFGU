#ifndef __BEVELED_WEDGE__
#define __BEVELED_WEDGE__

// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


// This file contains the definition of the class BeveledWedge

// The parameters are: 
//					inner and outer radii r0 and r1
//					minimum and maximum y extents y0 and y1
//					minimum and maximum azimuth angle extents phi0 and phi1
//					bevel radius rb
				
// There is no default constructor				
				
#include "Compound.h"

//-------------------------------------------------------------------------------- class BeveledWedge

class BeveledWedge: public Compound {
	public:
	
		BeveledWedge(	const double y0,		// minimum y value
						const double y1,		// minimum y value
						const double r0,		// inner radius
						const double r1,		// outer radius
						const double rb,		// bevel radius
						const double phi0,		// minimum azimuth angle in degrees
						const double phi1);		// maximum azimuth angle
		
							
		BeveledWedge(const BeveledWedge& bw); 				
		
		virtual BeveledWedge* 								
		clone(void) const;

		virtual BeveledWedge& 								
		operator= (const BeveledWedge& rhs);		
		
		virtual 											
		~BeveledWedge(void); 
		
		virtual BBox 
		get_bounding_box(void);
		
		virtual bool 																						 
		hit(const Ray& ray, double& tmin, ShadeRec& sr) const;
				
	private:
	
		double 	y0;		// minimum y value
		double 	y1;		// minimum y value
		double 	r0; 	// inner radius
		double 	r1;		// outer radius
		double 	rb;		// bevel radius
		double 	phi0;	// maximum azimuth angle
		double 	phi1;	// minimum azimuth angle

		BBox	bbox;	// bounding box
};

#endif
