// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

#include "PureRandom2D.h"
#include "Maths.h"
#include "Point2D.h"
#include "Constants.h"



PureRandom::PureRandom() : bundleSize_(DEFAULT_BUNDLE_SIZE) {}
PureRandom::PureRandom(int bundleSize) : bundleSize_(bundleSize) {}
PureRandom::~PureRandom() {}


const SampleBundle2D& PureRandom::get_next() {
    // Even though this generator doesn't need to keep the
    // samples, it does to satisfy the requirements of get_next.
    samples_.clear();
    generate_samples();
    return samples_;
}

void PureRandom::set_bundle_size(int bundleSize) {
    bundleSize_ = bundleSize;
}


int PureRandom::get_bundle_size() const {
    return bundleSize_;
}


void PureRandom::generate_samples() {
    for (int q = 0; q < bundleSize_; q++) {
        float x = rand_float();
        float y = rand_float();
        samples_.push_back(Point2D(x, y));
    }
}


