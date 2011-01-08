// This file contains the definition the ViewPlane class

#include "ViewPlane.h"
#include "Sampler.h"
#include "Regular.h"


ViewPlane::ViewPlane(void)
        : 	hres(400),
        vres(400),
        s(1.0),
        gamma(1.0),
        inv_gamma(1.0),
        show_out_of_gamut(false),
        sampler_(SamplerPtr(new Regular)) {}




ViewPlane::~ViewPlane(void) {}












