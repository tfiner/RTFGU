// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


#include "Rectangle.h"

const double Rectangle::kEpsilon = 0.001;

// ----------------------------------------------------------------  default constructor

Rectangle::Rectangle(void)
	: 	GeometricObject(),
		p0(-1, 0, -1), 
		a(0, 0, 2), b(2, 0, 0), 
		a_len_squared(4.0), 
		b_len_squared(4.0),
		normal(0, 1, 0),
		area(4.0),
		inv_area(0.25),
		sampler_ptr(NULL)
{}


// ----------------------------------------------------------------  constructor
// this constructs the normal

Rectangle::Rectangle(const Point3D& _p0, const Vector3D& _a, const Vector3D& _b)
	:	GeometricObject(),
		p0(_p0),
		a(_a),
		b(_b),
		a_len_squared(a.len_squared()), 
		b_len_squared(b.len_squared()),
		area(a.length() * b.length()),
		inv_area(1.0 / area),
		sampler_ptr(NULL)		
{
	normal = a ^ b;
	normal.normalize();
}


// ----------------------------------------------------------------  constructor
// this has the normal as an argument

Rectangle::Rectangle(const Point3D& _p0, const Vector3D& _a, const Vector3D& _b, const Normal& n)
	:	GeometricObject(),
		p0(_p0),
		a(_a),
		b(_b),
		a_len_squared(a.len_squared()), 
		b_len_squared(b.len_squared()),
		area(a.length() * b.length()),	
		inv_area(1.0 / area),
		normal(n),
		sampler_ptr(NULL)
{
	normal.normalize();
}



// ---------------------------------------------------------------- clone

Rectangle* 
Rectangle::clone(void) const {
	return (new Rectangle(*this));
}


// ---------------------------------------------------------------- copy constructor

Rectangle::Rectangle (const Rectangle& r)
	:	GeometricObject(r),
		p0(r.p0), 
		a(r.a),
		b(r.b),
		a_len_squared(r.a_len_squared), 
		b_len_squared(r.b_len_squared),	
		normal(r.normal),
		area(r.area),
		inv_area(r.inv_area)
{
	if(r.sampler_ptr)
		sampler_ptr	= r.sampler_ptr->clone(); 
	else  sampler_ptr = NULL;
}



// ---------------------------------------------------------------- assignment operator

Rectangle& 
Rectangle::operator= (const Rectangle& rhs) {
	if (this == &rhs)
		return (*this);

	GeometricObject::operator=(rhs);
	
	p0				= rhs.p0;
	a				= rhs.a;
	b				= rhs.b;
	a_len_squared	= rhs.a_len_squared; 
	b_len_squared	= rhs.b_len_squared;
	area			= rhs.area;	
	inv_area		= rhs.inv_area;
	normal			= rhs.normal;
	
	if (sampler_ptr) {
		delete sampler_ptr;
		sampler_ptr = NULL;
	}

	if (rhs.sampler_ptr)
		sampler_ptr= rhs.sampler_ptr->clone();

	return (*this);
}


// ---------------------------------------------------------------- destructor

Rectangle::~Rectangle (void) {

	if (sampler_ptr) {
		delete sampler_ptr;
		sampler_ptr = NULL;
	}
}

//------------------------------------------------------------------ get_bounding_box 

BBox
Rectangle::get_bounding_box(void) {
	double delta = 0.0001; 

	return(BBox(min(p0.x, p0.x + a.x + b.x) - delta, max(p0.x, p0.x + a.x + b.x) + delta,
				min(p0.y, p0.y + a.y + b.y) - delta, max(p0.y, p0.y + a.y + b.y) + delta, 
				min(p0.z, p0.z + a.z + b.z) - delta, max(p0.z, p0.z + a.z + b.z) + delta));
}
																			

//------------------------------------------------------------------ hit 

bool 												 
Rectangle::hit(const Ray& ray, double& tmin, ShadeRec& sr) const {	
	
	double t = (p0 - ray.o) * normal / (ray.d * normal); 
	
	if (t <= kEpsilon)
		return (false);
			
	Point3D p = ray.o + t * ray.d;
	Vector3D d = p - p0;
	
	double ddota = d * a;
	
	if (ddota < 0.0 || ddota > a_len_squared)
		return (false);
		
	double ddotb = d * b;
	
	if (ddotb < 0.0 || ddotb > b_len_squared)
		return (false);
		
	tmin 				= t;
	sr.normal 			= normal;
	sr.local_hit_point 	= p;
	
	return (true);
}


// ---------------------------------------------------------------- setSampler

void 								
Rectangle::set_sampler(Sampler* sampler) {
	sampler_ptr = sampler;
}


// ---------------------------------------------------------------- sample
// returns a sample point on the rectangle

Point3D 											
Rectangle::sample(void) {
	Point2D sample_point = sampler_ptr->sample_unit_square();
	return (p0 + sample_point.x * a + sample_point.y * b);
}


//------------------------------------------------------------------ get_normal 
					 
Normal 										
Rectangle::get_normal(const Point3D& p) {
	return (normal);
}


// ---------------------------------------------------------------- pdf

float
Rectangle::pdf(ShadeRec& sr) {	
	return (inv_area);
} 





