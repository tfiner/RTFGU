// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


// This file contains the definition of the class Rosette

// There are two versions of the function construct_rosette: one for Figure 21.11(a) and one for
// Figure 21.17 (commented out)


#include "Rosette.h"
#include "BeveledWedge.h"

const int Rosette::num_wedges[6] = {10, 12, 15, 18, 24, 36};  // these numbers exactly divide into 360

// ------------------------------------------------------------------------------ default constructor

Rosette::Rosette(void)
			:	Grid(),
				num_rings(1), 
				hole_radius(1.0),
				ring_width(1.0),
				rb(0.25),
				y0(-1.0),
				y1(1.0)
{
	construct_rosette();
}


// ------------------------------------------------------------------------------ constructor

Rosette::Rosette(	const int 	_num_rings, 
					const double	_hole_radius,
					const double _ring_width,
					const double _rb,
					const double _y0,
					const double _y1)

	:	Grid(),
		num_rings(_num_rings), 
		hole_radius(_hole_radius),
		ring_width(_ring_width),
		rb(_rb),
		y0(_y0),
		y1(_y1)
{
	construct_rosette();
}	

	
// ------------------------------------------------------------------------------ copy constructor

Rosette::Rosette(const Rosette& r)  			
			: 	Grid(r),
				num_rings(r.num_rings), 
				hole_radius(r.hole_radius),
				ring_width(r.ring_width),
				rb(r.rb),
				y0(r.y0),
				y1(r.y1)
{}

// ------------------------------------------------------------------------------ clone

Rosette* 
Rosette::clone(void) const {
	return(new Rosette(*this));
}


// ------------------------------------------------------------------------------ assignment operator

Rosette& 
Rosette::operator= (const Rosette& rhs) {
	if (this == &rhs)
		return (*this);

	Grid::operator= (rhs); 
	
	num_rings	= rhs.num_rings; 
	hole_radius	= rhs.hole_radius;
	ring_width  = rhs.ring_width;
	rb			= rhs.rb;
	y0			= rhs.y0;
	y1			= rhs.y1;

	return (*this) ;
}


// ------------------------------------------------------------------------------ destructor
 
Rosette::~Rosette(void) {}


// ------------------------------------------------------------------------------ construct_rosette
// this function constructs the wedges in a rosette pattern and stores them in a grid
// this is the regular version, for Figure 21.11
 
void
Rosette::construct_rosette(void) {	
	
	for (int k = 0; k < num_rings; k++) {
		for (int j = 0; j < num_wedges[k]; j++) {
			double angle_width = 360 / num_wedges[k];  // the azimuth angle extent of each wedge
			double r0 = hole_radius + k * ring_width;
			double r1 = hole_radius + (k + 1) * ring_width;
			double phi0 = j * angle_width;
			double phi1 = (j + 1) * angle_width;
			
			BeveledWedge* wedge_ptr = new BeveledWedge(y0, y1, r0, r1, rb, phi0 , phi1);
			add_object(wedge_ptr);										
		}
	}
}



/*

// ------------------------------------------------------------------------------ construct_rosette
// use this version to render Figure 21.17
 
void
Rosette::construct_rosette(void) {	
	
	for (int k = 0; k < num_rings; k++) {
		for (int j = 0; j < num_wedges[k]; j++) {
			double angle_width = 360 / num_wedges[k];  // the azimuth angle extent of each wedge
			double r0 = hole_radius + k * ring_width;
			double r1 = hole_radius + (k + 1) * ring_width;
			double angle_offset = 63 * k;			
			double phi0 = j * angle_width + angle_offset;
			double phi1 = (j + 1) * angle_width + angle_offset;
			
			BeveledWedge* wedge_ptr = new BeveledWedge(y0, y1, r0, r1, rb, phi0 , phi1);
			add_object(wedge_ptr);										
		}
	}
}


*/



											
																

