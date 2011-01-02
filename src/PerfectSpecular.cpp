// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


#include "PerfectSpecular.h"

// ---------------------------------------------------------- default constructor

PerfectSpecular::PerfectSpecular(void)
	: 	BRDF(),
		kr(0.0), 
		cr(1.0)
{}

// ---------------------------------------------------------- destructor

PerfectSpecular::~PerfectSpecular(void) {}


// ---------------------------------------------------------------------- clone

PerfectSpecular* 
PerfectSpecular::clone(void) const {
	return (new PerfectSpecular(*this));
}	


// ---------------------------------------------------------- f

RGBColor
PerfectSpecular::f(const ShadeRec& sr, const Vector3D& wo, const Vector3D& wi) const {
	return (black);
}


// ---------------------------------------------------------- sample_f
// this computes wi: the direction of perfect mirror reflection
// it's called from from the functions Reflective::shade and Transparent::shade.
// the fabs in the last statement is for transparency

RGBColor
PerfectSpecular::sample_f(const ShadeRec& sr, const Vector3D& wo, Vector3D& wi) const {
	float ndotwo = sr.normal * wo;
	wi = -wo + 2.0 * sr.normal * ndotwo; 
	return (kr * cr / fabs(sr.normal * wi)); // why is this fabs? // kr would be a Fresnel term in a Fresnel reflector
}											 // for transparency when ray hits inside surface?, if so it should go in Chapter 24


// ---------------------------------------------------------- sample_f
// this version of sample_f is used with path tracing
// it returns ndotwi in the pdf

RGBColor
PerfectSpecular::sample_f(const ShadeRec& sr, const Vector3D& wo, Vector3D& wi, float& pdf) const {
	float ndotwo = sr.normal * wo;
	wi = -wo + 2.0 * sr.normal * ndotwo; 
	pdf = fabs(sr.normal * wi);
	return (kr * cr);  
}

// ---------------------------------------------------------- rho

RGBColor
PerfectSpecular::rho(const ShadeRec& sr, const Vector3D& wo) const {
	return (black);
}

