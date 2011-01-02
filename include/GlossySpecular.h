#ifndef __GLOSSY_SPECULAR__
#define __GLOSSY_SPECULAR__

// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


// this implements glossy specular reflection for direct and indirect illumination

#include "BRDF.h"

class GlossySpecular: public BRDF {
	public:
	
		GlossySpecular(void);
		
		~GlossySpecular(void);
		
		virtual GlossySpecular*
		clone(void) const;
		
		virtual RGBColor
		f(const ShadeRec& sr, const Vector3D& wo, const Vector3D& wi) const;
				
		virtual RGBColor
		sample_f(const ShadeRec& sr, const Vector3D& wo, Vector3D& wi, float& pdf) const;
		
		virtual RGBColor
		rho(const ShadeRec& sr, const Vector3D& wo) const;
		
		void
		set_ks(const float ks);
		
		void
		set_exp(const float exp);
		
		void
		set_cs(const RGBColor& c);
		
		void													
		set_cs(const float r, const float g, const float b);
		
		void													
		set_cs(const float c);
		
		void
		set_sampler(Sampler* sp, const float exp);   			// any type of sampling
		
		void
		set_samples(const int num_samples, const float exp); 	// multi jittered sampling
		
		void
		set_normal(const Normal& n);
		
		
	private:
	
		float		ks;
		RGBColor 	cs;			// specular color
		float		exp; 		// specular exponent
		Sampler*	sampler;    // for use in sample_f
};


// -------------------------------------------------------------- set_ks

inline void
GlossySpecular::set_ks(const float k) {
	ks = k;
}

// -------------------------------------------------------------- set_exp

inline void
GlossySpecular::set_exp(const float e) {
	exp= e;
}


// -------------------------------------------------------------- set_cs

inline void
GlossySpecular::set_cs(const RGBColor& c) {
	cs = c;
}


// ---------------------------------------------------------------- set_cs

inline void													
GlossySpecular::set_cs(const float r, const float g, const float b) {
	cs.r = r; cs.g = g; cs.b = b;
}


// ---------------------------------------------------------------- set_cs

inline void													
GlossySpecular::set_cs(const float c) {
	cs.r = c; cs.g = c; cs.b = c;
}

#endif

