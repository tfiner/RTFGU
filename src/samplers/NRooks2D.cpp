// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

#include "NRooks2D.h"
#include "Constants.h"
#include "Maths.h"
#include "Point2D.h"
#include "shuffle.h"

#include <cassert>


NRooks2D::NRooks2D() : bundleSize_(DEFAULT_BUNDLE_SIZE) {}
NRooks2D::NRooks2D(int bundleSize) : bundleSize_(bundleSize) {}


const SampleBundle2D& NRooks2D::get_next() {
    samples_.clear();
    generate_samples();
    return samples_;
}


void NRooks2D::set_bundle_size(int bundleSize) {
    assert( is_square(bundleSize) &&
        "The number of samples in a bundle must be a square." );
    bundleSize_ = bundleSize;
}


int NRooks2D::get_bundle_size() const {
    return bundleSize_;
}


void NRooks2D::generate_samples(void) {
    for (int j = 0; j < bundleSize_; j++) {
        Point2D sp(
            (j + rand_float()) / bundleSize_,
            (j + rand_float()) / bundleSize_
        );
        samples_.push_back(sp);
    }

    shuffle_x_coords(samples_);
    shuffle_y_coords(samples_);
}

