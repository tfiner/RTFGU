// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

#include "Regular.h"

// ---------------------------------------------------------------- default constructor

Regular::Regular(): Sampler() {}


Regular::Regular(const int num):Sampler(num) {
    generate_samples();
}


Regular::Regular(const Regular& u): Sampler(u) {
    generate_samples();
}


Regular& Regular::operator= (const Regular& rhs) {
    if (this == &rhs)
        return (*this);

    Sampler::operator= (rhs);

    return (*this);
}


Regular* Regular::clone() const {
    return (new Regular(*this));
}

Regular::~Regular() {}


/*
    0  0.5  1
    ________
    | . | . |
    |---+---|
    | . | . |
    ---------
    ____________
    | . | . | . |
    | . | . | . |
    | . | . | . |
    -------------
*/
void Regular::generate_samples() {
    float n = sqrt((float)num_samples);
    float inv_n = 1 / n;
    float start = inv_n / 2.0f;
    int in = (int) n;

    for (int j = 0; j < num_sets; j++) {
        for (int p = 0; p < in; p++) {
            for (int q = 0; q < in; q++) {
                samples.push_back(Point2D(start + q*inv_n, start + p*inv_n));
            }
        }
    }
}


Point2D Regular::sample_unit_square() {
    Point2D pt = samples[count];
    count = (count + 1) % samples.size();
    return pt;
}

