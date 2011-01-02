// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


#include "Constants.h"
#include "ConvexPartSphere.h"

// ----------------------------------------------------------------  default constructor
// a default ConvexPartSphere is a whole sphere

ConvexPartSphere::ConvexPartSphere (void)	
	: 	GeometricObject(),
		center(0.0),
		radius(1.0),
		phi_min(0.0),			// in radians
		phi_max(TWO_PI),		// in radians	
		theta_min(0.0),			// in radians measured from top
		theta_max(PI),			// in radians measured from top
		cos_theta_min(1.0),
		cos_theta_max(-1.0)
{}


// ---------------------------------------------------------------- donstructor

ConvexPartSphere::ConvexPartSphere (const Point3D 	c, 
									const double 	r, 
									const double 	azimuth_min,	// in degrees
									const double 	azimuth_max,	// in degrees
									const double 	polar_min,		// in degrees measured from top
									const double 	polar_max)		// in degrees measured from top
	: 	GeometricObject(),
		center(c),
		radius(r),
		phi_min(azimuth_min * PI_ON_180),			// in radians
		phi_max(azimuth_max * PI_ON_180),			// in radians
		theta_min(polar_min * PI_ON_180),			// in radians measured from top
		theta_max(polar_max * PI_ON_180),			// in radians measured from top
		cos_theta_min(cos(theta_min)),
		cos_theta_max(cos(theta_max))
{}


// ---------------------------------------------------------------- constructor

ConvexPartSphere::ConvexPartSphere (const Point3D 	c, 
									const double 	r)
	: 	GeometricObject(),
		center(c),
		radius(r),
		phi_min(0.0),
		phi_max(TWO_PI),
		theta_min(0.0),
		theta_max(PI),
		cos_theta_min(1.0),
		cos_theta_max(-1.0)
{}


// ---------------------------------------------------------------- clone

ConvexPartSphere* 
ConvexPartSphere::clone(void) const {
	return (new ConvexPartSphere(*this));
}


// ---------------------------------------------------------------- copy constructor

ConvexPartSphere::ConvexPartSphere (const ConvexPartSphere& ps)
	: 	GeometricObject(ps),
		center(ps.center),
		radius(ps.radius),
		phi_min(ps.phi_min),
		phi_max(ps.phi_max),
		theta_min(ps.theta_min),
		theta_max(ps.theta_max),
		cos_theta_min(ps.cos_theta_min),
		cos_theta_max(ps.cos_theta_max) 
{}



// ---------------------------------------------------------------- assignment operator

ConvexPartSphere& 
ConvexPartSphere::operator= (const ConvexPartSphere& rhs)		
{
	if (this == &rhs)
		return (*this);

	GeometricObject::operator=(rhs);

	center 			= rhs.center;
	radius			= rhs.radius;
	phi_min			= rhs.phi_min;
	phi_max			= rhs.phi_max;
	theta_min		= rhs.theta_min;
	theta_max		= rhs.theta_max;
	cos_theta_min	= rhs.cos_theta_min;
	cos_theta_max	= rhs.cos_theta_max; 

	return (*this);
}


// ---------------------------------------------------------------- destructor

ConvexPartSphere::~ConvexPartSphere(void) {}


// ------------------------------------------------------------------------------ hit

bool 															 
ConvexPartSphere::hit(const Ray& ray, double& tmin, ShadeRec& sr) const {
	double 		t;
	Vector3D  	temp 	= ray.o - center;
	double 		a 		= ray.d * ray.d;
	double 		b 		= 2.0 * temp * ray.d;
	double 		c 		= temp * temp - radius * radius;
	double 		disc 	= b * b - 4.0 * a * c;
	
	if (disc < 0.0)
		return(false);
	else {	
		double e = sqrt(disc);
		double denom = 2.0 * a;
		t = (-b - e) / denom;    // smaller root
		
		if (t > kEpsilon) {
			Vector3D hit = ray.o + t * ray.d - center;
			
			double phi = atan2(hit.x, hit.z);
			if (phi < 0.0)
				phi += TWO_PI;
			
			if (hit.y <= radius * cos_theta_min && 	
				hit.y >= radius * cos_theta_max && 	
				phi >= phi_min && phi <= phi_max) {
				
				tmin = t;				
				sr.normal = (temp + t * ray.d) / radius;   // points outwards
				sr.local_hit_point = ray.o + tmin * ray.d;				
				return (true);
			}
		} 
		
		t = (-b + e) / denom;    // larger root
		
		if (t > kEpsilon) {
			Vector3D hit = ray.o + t * ray.d - center;
		
			double phi = atan2(hit.x, hit.z);
			if (phi < 0.0)
				phi += TWO_PI;
			
			if (hit.y <= radius * cos_theta_min && 	
				hit.y >= radius * cos_theta_max && 	
				phi >= phi_min && phi <= phi_max) {
				
				tmin = t;				
				sr.normal = (temp + t * ray.d) / radius;   // points outwards
				sr.local_hit_point = ray.o + tmin * ray.d;				
				return (true);
			}
		} 
	}
	
	return (false);
}
	


