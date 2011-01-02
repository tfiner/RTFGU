// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


#include "OpenCylinder.h"

// This uses the value of kEpsilon defined in Constants.h

// ---------------------------------------------------------------- default constructor

OpenCylinder::OpenCylinder(void)
	: 	GeometricObject(),
		y0(-1.0),
		y1(1.0),
		radius(1.0),
		inv_radius(1.0)			
{}

// ---------------------------------------------------------------- constructor

OpenCylinder::OpenCylinder(const double bottom, const double top, const double r)
	:  	GeometricObject(),
		y0(bottom),
		y1(top),	
		radius(r),
		inv_radius(1.0 / radius)
{}


// ---------------------------------------------------------------- copy constructor

OpenCylinder::OpenCylinder(const OpenCylinder& c)
	: 	GeometricObject(c),
		y0(c.y0),
		y1(c.y1),
		radius(c.radius), 
		inv_radius(c.inv_radius) 			
{}
																				
																				
// ---------------------------------------------------------------- clone

OpenCylinder* 
OpenCylinder::clone(void) const {
	return (new OpenCylinder (*this));
}																				
																																											

// ---------------------------------------------------------------- assignment operator

OpenCylinder& 
OpenCylinder::operator= (const OpenCylinder& rhs) 		
{
	if (this == &rhs)
		return (*this);

	GeometricObject::operator= (rhs);
	
	y0 			= rhs.y0;
	y1 			= rhs.y1;
	radius 		= rhs.radius;
	inv_radius 	= rhs.inv_radius;

	return (*this) ;
}


// ---------------------------------------------------------------- destructor

OpenCylinder::~OpenCylinder(void) {}


// ----------------------------------------------------------------------------- hit
// The code reverses the normal when the ray hits the inside surface, allows both
// sides to be shaded, but completely messes up transparency.

bool 															 
OpenCylinder::hit(const Ray& ray, double& tmin, ShadeRec& sr) const {
															
	double t;
	double ox = ray.o.x;
	double oy = ray.o.y;
	double oz = ray.o.z;
	double dx = ray.d.x;
	double dy = ray.d.y;
	double dz = ray.d.z;
	
	double a = dx * dx + dz * dz;  	
	double b = 2.0 * (ox * dx + oz * dz);					
	double c = ox * ox + oz * oz - radius * radius;
	double disc = b * b - 4.0 * a * c ;

			
	if (disc < 0.0)
		return(false);
	else {	
		double e = sqrt(disc);
		double denom = 2.0 * a;
		t = (-b - e) / denom;    // smaller root
		
		if (t > kEpsilon) {
			double yhit = oy + t * dy;
			
			if (yhit > y0 && yhit < y1) {
				tmin = t;
				sr.normal = Normal((ox + t * dx) * inv_radius, 0.0, (oz + t * dz) * inv_radius);
				
				// test for hitting from inside
			
				if (-ray.d * sr.normal < 0.0)
					sr.normal = -sr.normal;
					
				sr.local_hit_point = ray.o + tmin * ray.d;
				
				return (true);
			}
		} 
		
		t = (-b + e) / denom;    // larger root
		
		if (t > kEpsilon) {
			double yhit = oy + t * dy;
			
			if (yhit > y0 && yhit < y1) {
				tmin = t;
				sr.normal = Normal((ox + t * dx) * inv_radius, 0.0, (oz + t * dz) * inv_radius);
				
				// test for hitting inside surface
			
				if (-ray.d * sr.normal < 0.0)
					sr.normal = -sr.normal;
					
				sr.local_hit_point = ray.o + tmin * ray.d;
	
				return (true);
			}
		} 
	}
	
	return (false);			
}



