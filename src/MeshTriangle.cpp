// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

// the copy constructor and assignment operator do not clone the mesh

#include "Constants.h"
#include "MeshTriangle.h"
#include "Maths.h"
						

// ----------------------------------------------------------------  default constructor

MeshTriangle::MeshTriangle(void)
	: 	GeometricObject(),
		mesh_ptr(NULL),
		index0(0), index1(0), index2(0),
		normal()
{}


// ---------------------------------------------------------------- constructor
// the normal is computed in Grid::read_ply_file

MeshTriangle::MeshTriangle(Mesh* _mesh_ptr, const int i0, const int i1, const int i2)
	: 	GeometricObject(),
		mesh_ptr(_mesh_ptr),
		index0(i0), index1(i1), index2(i2) 
{}


// ---------------------------------------------------------------- copy constructor

MeshTriangle::MeshTriangle (const MeshTriangle& mt)
	:	GeometricObject(mt),
		mesh_ptr(mt.mesh_ptr), // just the pointer
		index0(mt.index0), 
		index1(mt.index1), 
		index2(mt.index2),
		normal(mt.normal)
{}


// ---------------------------------------------------------------- assignment operator

MeshTriangle& 
MeshTriangle::operator= (const MeshTriangle& rhs) {
	if (this == &rhs)
		return (*this);

	GeometricObject::operator= (rhs);
	
	mesh_ptr 	= rhs.mesh_ptr; // just the pointer
	index0 		= rhs.index0;
	index1 		= rhs.index1;
	index2 		= rhs.index2;
	normal 		= rhs.normal;
	
	return (*this);
}


// ---------------------------------------------------------------- destructor

MeshTriangle::~MeshTriangle (void) {
	if (mesh_ptr) {
		delete mesh_ptr;
		mesh_ptr = NULL;
	}
}


// ---------------------------------------------------------------- compute_normal

void 
MeshTriangle::compute_normal(const bool reverse_normal) {
	normal = (mesh_ptr->vertices[index1] - mesh_ptr->vertices[index0]) ^
			 (mesh_ptr->vertices[index2] - mesh_ptr->vertices[index0]);
	normal.normalize();
	
	if (reverse_normal)
		normal = -normal;
}


// ---------------------------------------------------------------- get_normal
// this is called in Grid::compute_mesh_normals

Normal
MeshTriangle::get_normal(void) const {
	return (normal);
}	


//---------------------------------------------------------------- get_bounding_box

BBox
MeshTriangle::get_bounding_box(void) {	
	double delta = 0.0001;  // to avoid degenerate bounding boxes
	
	Point3D v1(mesh_ptr->vertices[index0]);
	Point3D v2(mesh_ptr->vertices[index1]);
	Point3D v3(mesh_ptr->vertices[index2]);
	
	return(BBox(min(min(v1.x, v2.x), v3.x) - delta, max(max(v1.x, v2.x), v3.x) + delta, 
				min(min(v1.y, v2.y), v3.y) - delta, max(max(v1.y, v2.y), v3.y) + delta, 
				min(min(v1.z, v2.z), v3.z) - delta, max(max(v1.z, v2.z), v3.z) + delta));
}


// ------------------------------------------------------------------------------ shadow_hit
// this function is independent of the derived triangle type:
// flat, smooth, flat uv, smooth uv

bool 															 
MeshTriangle::shadow_hit(const Ray& ray, double& tmin) const {	
	Point3D v0(mesh_ptr->vertices[index0]);
	Point3D v1(mesh_ptr->vertices[index1]);
	Point3D v2(mesh_ptr->vertices[index2]);

	double a = v0.x - v1.x, b = v0.x - v2.x, c = ray.d.x, d = v0.x - ray.o.x; 
	double e = v0.y - v1.y, f = v0.y - v2.y, g = ray.d.y, h = v0.y - ray.o.y;
	double i = v0.z - v1.z, j = v0.z - v2.z, k = ray.d.z, l = v0.z - ray.o.z;
		
	double m = f * k - g * j, n = h * k - g * l, p = f * l - h * j;
	double q = g * i - e * k, s = e * j - f * i;
	
	double inv_denom  = 1.0 / (a * m + b * q + c * s);
	
	double e1 = d * m - b * n - c * p;
	double beta = e1 * inv_denom;
	
	if (beta < 0.0)
	 	return (false);
	
	double r = r = e * l - h * i;
	double e2 = a * n + d * q + c * r;
	double gamma = e2 * inv_denom;
	
	if (gamma < 0.0 )
	 	return (false);
	
	if (beta + gamma > 1.0)
		return (false);
			
	double e3 = a * p - b * r + d * s;
	double t = e3 * inv_denom;
	
	if (t < kEpsilon) 
		return (false);
                                                                                                       					
	tmin = t;
	
	return (true);	
}   


// ---------------------------------------------------------------- interpolate_u
// this is used for texture mapping in Chapter 29

float 
MeshTriangle::interpolate_u(const float beta, const float gamma) const {	
	return( (1 - beta - gamma) * mesh_ptr->u[index0] 
				+ beta * mesh_ptr->u[index1] 
					+ gamma * mesh_ptr->u[index2] );
}


// ---------------------------------------------------------------- interpolate_v
// this is used for texture mapping in Chapter 29

float 
MeshTriangle::interpolate_v(const float beta, const float gamma) const {	
	return( (1 - beta - gamma) * mesh_ptr->v[index0] 
				+ beta * mesh_ptr->v[index1] 
					+ gamma * mesh_ptr->v[index2] );
}


