// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

#include "Constants.h"
#include "Maths.h"
#include "SmoothTriangle.h"

// ----------------------------------------------------------------  default constructor

SmoothTriangle::SmoothTriangle(void)
	:	GeometricObject(),
		v0(0.0), 	
		v1(0,0,1), 
		v2(1,0,0),
		n0(0, 1, 0),   	
		n1(0, 1, 0),
		n2(0, 1, 0)
{}


// ---------------------------------------------------------------- constructor

SmoothTriangle::SmoothTriangle(const Point3D& a, const Point3D& b, const Point3D& c)
	:	GeometricObject(),	
		v0(a),
		v1(b),
		v2(c),
		n0(0, 1, 0),  
		n1(0, 1, 0),
		n2(0, 1, 0)
{}


// ---------------------------------------------------------------- clone

SmoothTriangle* 
SmoothTriangle::clone(void) const {
	return (new SmoothTriangle (*this));
}


// ---------------------------------------------------------------- copy constructor

SmoothTriangle::SmoothTriangle (const SmoothTriangle& st)
	:	GeometricObject(st),
		v0(st.v1),
		v1(st.v1),
		v2(st.v2),
		n0(st.n0),
		n1(st.n1),
		n2(st.n2)
{}


// ---------------------------------------------------------------- assignment operator

SmoothTriangle& 
SmoothTriangle::operator= (const SmoothTriangle& rhs) {
	if (this == &rhs)
		return (*this);

	v0 = rhs.v0;
	v1 = rhs.v1;
	v2 = rhs.v2;
	n0 = rhs.n0;
	n1 = rhs.n1;
	n2 = rhs.n2;
	
	return (*this);
}


// ---------------------------------------------------------------- destructor

SmoothTriangle::~SmoothTriangle(void) {}


// ---------------------------------------------------------------- computeNormal

Normal 
SmoothTriangle::interpolate_normal(const float beta, const float gamma) const {	
	Normal normal((1 - beta - gamma) * n0 + beta * n1 + gamma * n2);
	normal.normalize();
	
	return(normal);
}


//---------------------------------------------------------------- get_bounding_box

BBox
SmoothTriangle::get_bounding_box(void) {
	double delta = 0.0001; 
	
	return(BBox(min(min(v0.x, v1.x), v2.x) - delta, max(max(v0.x, v1.x), v2.x) + delta, 
				min(min(v0.y, v1.y), v2.y) - delta, max(max(v0.y, v1.y), v2.y) + delta, 
				min(min(v0.z, v1.z), v2.z) - delta, max(max(v0.z, v1.z), v2.z) + delta));
}



// ------------------------------------------------------------------------------ hit

bool 
SmoothTriangle::hit(const Ray& ray, double& tmin, ShadeRec& sr) const {	
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
	
	if (gamma < 0.0)
	 	return (false);
	
	if (beta + gamma > 1.0)
		return (false);
			
	double e3 = a * p - b * r + d * s;
	double t = e3 * inv_denom;
	
	if (t < kEpsilon)
		return (false);
					
	tmin 				= t;
	sr.normal 			= interpolate_normal(beta, gamma); 
	sr.local_hit_point 	= ray.o + t * ray.d;	
	
	return (true);	
}  	

	

// ------------------------------------------------------------------------------ shadow_hit
// Hit function for shadow rays

bool 																						 
SmoothTriangle::shadow_hit(const Ray& ray, double& tmin) const {	
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
					
	tmin = t;
	
	return(true);	
}  
