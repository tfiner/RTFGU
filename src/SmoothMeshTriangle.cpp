// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


#include "Constants.h"
#include "SmoothMeshTriangle.h"
						

// ----------------------------------------------------------------  default constructor

SmoothMeshTriangle::SmoothMeshTriangle(void)
	: 	MeshTriangle()
{}


// ---------------------------------------------------------------- constructor

SmoothMeshTriangle::SmoothMeshTriangle (Mesh* _mesh_ptr, const int i0, const int i1, const int i2)
	: 	MeshTriangle(_mesh_ptr, i0, i1, i2)
{}


// ---------------------------------------------------------------- clone

SmoothMeshTriangle* 
SmoothMeshTriangle::clone (void) const {
	return (new SmoothMeshTriangle (*this));
}


// ---------------------------------------------------------------- copy constructor

SmoothMeshTriangle::SmoothMeshTriangle (const SmoothMeshTriangle& fmt)
	:	MeshTriangle(fmt)
{}


// ---------------------------------------------------------------- assignment operator

SmoothMeshTriangle& 
SmoothMeshTriangle::operator= (const SmoothMeshTriangle& rhs) {
	if (this == &rhs)
		return (*this);

	MeshTriangle::operator= (rhs);
	
	return (*this);
}


// ---------------------------------------------------------------- destructor

SmoothMeshTriangle::~SmoothMeshTriangle(void) {}


// ---------------------------------------------------------------- interpolate_normal

Normal 
SmoothMeshTriangle::interpolate_normal(const float beta, const float gamma) const {	
	Normal normal((1 - beta - gamma) * mesh_ptr->normals[index0] 
						+ beta * mesh_ptr->normals[index1] 
								+ gamma * mesh_ptr->normals[index2]);
	normal.normalize();
	
	return(normal);
}

// ---------------------------------------------------------------- hit

bool 															 
SmoothMeshTriangle::hit(const Ray& ray, double& tmin, ShadeRec& sr) const {		
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
	
	double r = e * l - h * i;
	double e2 = a * n + d * q + c * r;
	double gamma = e2 * inv_denom;
	
	if (gamma < 0.0)
	 	return (false);
	
	if (beta + gamma > 1.0)
		return (false);
			
	double e3 = a * p - b * r + d * s;
	double t = e3 * inv_denom;
	
	if (t < kEpsilon)
		return (false);
					
	tmin 				= t;
	sr.normal 			= interpolate_normal(beta, gamma); // for smooth shading
	sr.local_hit_point 	= ray.o + t * ray.d;	
	
	return (true);	
}  

