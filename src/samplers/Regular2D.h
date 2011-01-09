#ifndef __REGULAR__
#define __REGULAR__


// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


#include "Sampler.h"
#include "Point2D.h"

class Regular2D : public SampleGenerator2D {
public:
    Regular2D();
    Regular2D(int bundleSize);
    ~Regular2D();

    const SampleBundle2D& get_next();

    void set_bundle_size(size_t samples);
    int get_bundle_size() const;

private:
    int bundleSize_;
    SampleBundle samples_;
    void generate_samples();
};


#endif

