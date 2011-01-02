#ifndef __INSTANCE__
#define __INSTANCE__

// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


// This includes a bounding box, instead of computing it. 
// This uses extra memory but the object to be transformed may be a grid or some other complex object
// whose bouding box is expensive to compute.

#include "GeometricObject.h"
#include "Matrix.h"

class Instance: public GeometricObject {	
	public:
		
		Instance(void);   									
		
		Instance(GeometricObject* obj_ptr);					
		
		Instance(const Instance& instance); 
		
		virtual Instance* 									
		clone(void) const;				

		virtual												
		~Instance(void); 
		
		Instance& 											
		operator= (const Instance& rhs);
				
		void 												
		set_object(GeometricObject* obj_ptr);	
		
		void
		transform_texture(const bool transform);
			
		virtual void 										
		compute_bounding_box(void);
		
		virtual BBox 										
		get_bounding_box(void);					
											
		virtual Material* 									
		get_material(void) const;  								
				
		virtual void 							 	
		set_material(Material* materialPtr);
				
		virtual bool 												 
		hit(const Ray& ray, double& tmin, ShadeRec& sr) const;
		
		
		// affine tranformation functions
		
		void												
		translate(const Vector3D& trans);
		
		void
		translate(const double dx, const double dy, const double dz);	
		
		void												
		scale(const Vector3D& s);
		
		void 
		scale(const double a, const double b, const double c);
		
		virtual void										
		rotate_x(const double r);
		
		virtual void										
		rotate_y(const double r);
		
		virtual void										
		rotate_z(const double r);
		
		void												
		shear(const Matrix& m);
		
		
	private:

		GeometricObject*	object_ptr;				// object to be transformed
		Matrix				inv_matrix;		    	// inverse transformation matrix
		static 	Matrix		forward_matrix; 		// transformation matrix
		BBox				bbox;					// transformed object's bounding box
		bool				transform_the_texture;	// do we transform the texture?
			

};


inline void
Instance::transform_texture(const bool transform) {
	transform_the_texture = transform;
}	

#endif
