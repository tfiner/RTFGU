// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

#include "MultiJittered2D.h"
#include "Constants.h"
#include "Maths.h"
#include "Point2D.h"
#include "shuffle.h"

#include <cassert>


MultiJittered2D::MultiJittered2D() : bundleSize_(DEFAULT_BUNDLE_SIZE) {}
MultiJittered2D::MultiJittered2D(int bundleSize) : bundleSize_(bundleSize) {}


void MultiJittered2D::set_bundle_size(int bundleSize) {
    assert( is_square(bundleSize) && "The number of samples in a bundle must be a square." );
    bundleSize_ = bundleSize;
}


int MultiJittered2D::get_bundle_size() const { return bundleSize_; }


// Always generates new jittered samples.
// IFF performance is wanting, then I'll come back and perhaps do some more precalculation.
// Initial observed runs with the simpler, naive code is that runs pretty damn fast.  I think that
// the optimization I made of returning all the samples per pixel (reducing the number of
// function calls) improved the speed to where the precalcuation is of negligible benefit.
const SampleBundle2D& MultiJittered2D::get_next() {
    samples_.clear();
    generate_samples();
    return samples_;
}


// This is based on code in Chui et al. (1994), cited in the references
void MultiJittered2D::generate_samples() {
    // num_samples needs to be a perfect square

    int n = (int)sqrt((float)bundleSize_);
    float subcell_width = 1.0 / ((float) bundleSize_);

    // fill the samples array with dummy points to allow us to use the [ ] notation when we set the
    // initial patterns

    Point2D fill_point;
    for (int j = 0; j < bundleSize_; j++)
        samples_.push_back(fill_point);

    // distribute points in the initial patterns
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            samples_[i * n + j].x =
                (i * n + j) * subcell_width + rand_float(0, subcell_width);

            samples_[i * n + j].y =
                (j * n + i) * subcell_width + rand_float(0, subcell_width);
        }
    }

    shuffle_x_coords(samples_);
    shuffle_y_coords(samples_);
}


