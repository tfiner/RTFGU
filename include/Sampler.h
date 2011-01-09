#ifndef __SAMPLER__
#define __SAMPLER__


// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


#include <vector>


/*  An interface to return samples generated from sampling algorithms.

*/
template<typename SampleUnit>
class SampleGenerator {
public:
    typedef std::vector<SampleUnit> SampleBundle;

    virtual ~SampleGenerator() {}

    // Returns const so that samplers can return their
    // internal representation without copying.  This is
    // useful for samplers that return a cached or constant
    // SampleBundle.
    virtual const SampleBundle& get_next() = 0;


    virtual void set_unit_size(size_t samples) = 0;
    virtual int get_unit_size() const = 0;
};

#endif

