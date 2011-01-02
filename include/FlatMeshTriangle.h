#ifndef __FLAT_MESH_TRIANGLE__
#define __FLAT_MESH_TRIANGLE__


// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


// FlatMeshTriangle is a MeshTriangle that uses flat shading with a constant normal
// This uses the inherited shadow hit function from MeshTriangle

#include "MeshTriangle.h"

class FlatMeshTriangle: public MeshTriangle {	
	public:
		
		FlatMeshTriangle(void);   									
		
		FlatMeshTriangle(Mesh* _meshPtr, const int i0, const int i1, const int i2);		

		virtual FlatMeshTriangle* 										
		clone(void) const;
	
		FlatMeshTriangle(const FlatMeshTriangle& fmt); 					

		virtual
		~FlatMeshTriangle(void);   									

		FlatMeshTriangle& 												
		operator= (const FlatMeshTriangle& rhs);
				
		virtual	bool
		hit(const Ray& ray, double& tmin, ShadeRec& sr) const; 																	
};

#endif

