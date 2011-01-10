#ifndef __JITTERED__
#define __JITTERED__


// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


#include "SampleGenerator.h"


class Jittered2D : public SampleGenerator2D {
public:
    Jittered2D();
    Jittered2D(int bundleSize);

    virtual const SampleBundle2D& get_next();

    virtual void set_bundle_size(int bundleSize);
    virtual int get_bundle_size() const;


private:
    int bundleSize_;
    SampleBundle samples_;
    void generate_samples();

};

#endif

