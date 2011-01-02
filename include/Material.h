#ifndef __MATERIAL__
#define __MATERIAL__


// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


#include "World.h"			// required for the shade function in all derived classes
#include "RGBColor.h"
#include "ShadeRec.h"

class Material {	
	public:
	
		Material(void);						
		
		Material(const Material& material); 
		
		virtual Material*								
		clone(void) const = 0;	
				
		virtual 								
		~Material(void);
				
		virtual RGBColor
		shade(ShadeRec& sr);	
		
	protected:
	
		Material& 								
		operator= (const Material& rhs);						
};

#endif

