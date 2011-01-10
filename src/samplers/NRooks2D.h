#ifndef __N_ROOKS__
#define __N_ROOKS__


// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


#include "SampleGenerator.h"

class NRooks2D: public SampleGenerator2D {
public:
    NRooks2D(void);
    NRooks2D(const int num_samples);

    const SampleBundle2D& get_next();
    void set_bundle_size(int bundleSize);
    int get_bundle_size() const;

private:
    int bundleSize_;
    SampleBundle2D samples_;
    void generate_samples();
};

#endif

