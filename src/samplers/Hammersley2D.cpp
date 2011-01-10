// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

#include "Hammersley2D.h"
#include "Constants.h"
#include "Point2D.h"


Hammersley2D::Hammersley2D() : bundleSize_(DEFAULT_BUNDLE_SIZE) {}
Hammersley2D::Hammersley2D(int bundleSize) : bundleSize_(bundleSize){}


const SampleBundle2D& Hammersley2D::get_next() {
    if ( samples_.empty() )
        generate_samples();

    return samples_;
}


void Hammersley2D::set_bundle_size(int bundleSize) {
    bundleSize_ = bundleSize;
    samples_.clear();
}


int Hammersley2D::get_bundle_size() const {
    return bundleSize_;
}


void Hammersley2D::generate_samples() {
    for ( int k=0; k < bundleSize_; k++ ) {
        float u = 0;
        int kk=k;
        for (float p=0.5; kk; p*=0.5, kk>>=1){
            // kk mod 2 == 1
            if (kk & 1)
                u += p;
        }
        float v = (k + 0.5) / bundleSize_;
        samples_.push_back( Point2D(u, v) );
    }
}
