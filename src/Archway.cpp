// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


// This file contains the definition of the class Archway

#include "Archway.h"
#include "BeveledBox.h"
#include "BeveledWedge.h"

// ------------------------------------------------------------------------------ constructor

Archway::Archway(	const double _width,		
					const double _height,		
					const double _depth,	
					const double _column_width,
					const double _num_blocks,
					const double _num_wedges,
					const double _rb)

	:	Grid(),
		width(_width),
		height(_height),
		depth(_depth),
		column_width(_column_width),
		num_blocks(_num_blocks),
		num_wedges(_num_wedges),
		rb(_rb)
{	
	construct_archway();
}


// ------------------------------------------------------------------------------ copy constructor

Archway::Archway(const Archway& aw)  			
			: 	Grid(aw),
				width(aw.width),
				height(aw.height),
				depth(aw.depth),
				column_width(aw.column_width),
				num_blocks(aw.num_blocks),
				num_wedges(aw.num_wedges),
				rb(aw.rb)
{}

// ------------------------------------------------------------------------------ clone

Archway* 
Archway::clone(void) const {
	return(new Archway(*this));
}


// ------------------------------------------------------------------------------ assignment operator

Archway& 
Archway::operator= (const Archway& rhs) {
	if (this == &rhs)
		return (*this);

	Grid::operator= (rhs);
	
	width 			= rhs.width;
	height 			= rhs.height;
	depth 			= rhs.depth;
	column_width 	= rhs.column_width;
	num_blocks 		= rhs.num_blocks;
	num_wedges 		= rhs.num_wedges;
	rb 				= rhs.rb; 

	return (*this) ;
}


// ------------------------------------------------------------------------------ destructor
 
Archway::~Archway(void) {}


// ------------------------------------------------------------------------------ construct_archway

void
Archway::construct_archway(void) {

	double block_height = (height - width / 2.0) / num_blocks;
	
	// build left column
			
	for (int j = 0; j < num_blocks; j++) {
		Point3D p0(-(height - width / 2.0) + j * block_height, 0.0, - width / 2.0);
		Point3D p1(-(height - width / 2.0) + (j + 1) * block_height, depth, - width / 2.0 + column_width);
		BeveledBox* block_ptr = new BeveledBox(p0, p1, rb);
		add_object(block_ptr);
	}
	
	// build right column
			
	for (int j = 0; j < num_blocks; j++) {
		Point3D p0(-(height - width / 2.0) + j * block_height, 0.0, width / 2.0 - column_width);
		Point3D p1(-(height - width / 2.0) + (j + 1) * block_height, depth, width / 2.0);
		BeveledBox* block_ptr = new BeveledBox(p0, p1, rb);
		add_object(block_ptr);
	}
	
	// build curved arch
	
	for (int j = 0; j < num_wedges; j++) {
		double angle_width = 180 / num_wedges;  // the azimuth angle extent of each wedge
		double r0 = width / 2.0 - column_width;
		double r1 = width / 2.0;
		double phi0 = j * angle_width; 
		double phi1 = (j + 1) * angle_width; 
		
		BeveledWedge* wedge_ptr = new BeveledWedge(0.0, depth, r0, r1, rb, phi0 , phi1);
		add_object(wedge_ptr);											
	}
}





																			
															
																
