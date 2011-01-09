#ifndef __REGULAR__
#define __REGULAR__


// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


#include "Sampler.h"

class Regular: public Sampler {
public:
    Regular();
    Regular(const int num);
    Regular(const Regular& u);

    Regular& operator= (const Regular& rhs);

    virtual Regular* clone() const;

    virtual ~Regular();

    virtual void generate_samples();

    virtual Point2D sample_unit_square();
};

#endif

