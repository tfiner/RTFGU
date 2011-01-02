#ifndef __MESH__
#define __MESH__


// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


// A mesh object stores the data for mesh triangles:
//
//			vertices
//			normals
//			uv texture coordinates
//			lists of triangles that share each vertex
//
// Mesh triangles are stored in a grid, which has a pointer to the mesh
// Each mesh triangle also has a pointer to the mesh
// The Mesh class does not inherit from GeometricObject

#include <vector>

#include "Point3D.h"
#include "Normal.h"

class Mesh {
	public:

		std::vector<Point3D> 		vertices;				// mesh vertices
		std::vector<Normal> 			normals;				// average normal at each vertex;
		std::vector<float>			u;						// u texture coordinate at each vertex
		std::vector<float>			v;						// v texture coordinate at each vertex
		std::vector<std::vector<int> > 	vertex_faces;			// the triangles shared by each vertex
		int 					num_vertices; 			// number of vertices
		int 					num_triangles; 			// number of triangles

		Mesh(void);

		Mesh(const Mesh& m);

		~Mesh(void);

		Mesh&
		operator= (const Mesh& rhs);
};

#endif


