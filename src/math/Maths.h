#ifndef __MATHS__
#define __MATHS__


// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


// This is a header file for the mathematics utility functions
// The prototypes of any inlined functions must be placed here

#include <stdlib.h>
#include <cmath>

#include "Constants.h"


inline bool is_square(float val) {
    double intPart = 0.0;
    double fracPart = modf((double)val, &intPart);
    return 0.0 == fracPart;
}

// a wrapper for rand()
inline int rand_int() {
    return rand();
}


inline float rand_float() {
    return (float)rand_int() * invRAND_MAX;
}


inline void set_rand_seed(const int seed) {
    srand(seed);
}


// The following two functions are only for multi-jittered sampling
// I had trouble getting them to compile in the MultiJittered class
// The overloading confused my compiler
inline float rand_float(int l, float h) {
    return rand_float() * (h - l) + l;
}

inline int rand_int(int l, int h) {
    return (int) (rand_float(0, h - l + 1) + l);
}


inline double clamp(const double x, const double min, const double max) {
    return x < min ? min : (x > max ? max : x);
}

int SolveQuadric(double c[3], double s[2]);
int SolveCubic(double c[4], double s[3]);
int SolveQuartic(double c[5], double s[4]);


#endif
