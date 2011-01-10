// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

#include "Jittered2D.h"
#include "Constants.h"
#include "Maths.h"
#include "Point2D.h"

#include <cassert>

Jittered2D::Jittered2D() : bundleSize_(DEFAULT_BUNDLE_SIZE) {}
Jittered2D::Jittered2D(int bundleSize) : bundleSize_(bundleSize) {}


void Jittered2D::set_bundle_size(int bundleSize) {
    assert( is_square(bundleSize) && "The number of samples in a bundle must be a square." );
    bundleSize_ = bundleSize;
}


int Jittered2D::get_bundle_size() const { return bundleSize_; }


// Always genertes new jittered samples.
const SampleBundle2D& Jittered2D::get_next() {
    samples_.clear();
    generate_samples();
    return samples_;
}


void Jittered2D::generate_samples(void) {
    int n = (int) sqrt((float)bundleSize_);
    for (int j = 0; j < n; j++) {
        for (int k = 0; k < n; k++) {
            Point2D sp((k + rand_float()) / n, (j + rand_float()) / n);
            samples_.push_back(sp);
        }
    }
}

