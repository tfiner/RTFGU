// This file contains the definition the ViewPlane class

#include "ViewPlane.h"
#include "Sampler.h"
#include "Regular.h"


ViewPlane::ViewPlane(): hres(400), vres(400),
        gamma(1.0), inv_gamma(1.0),
        show_out_of_gamut(false),
        sampler_(SamplerPtr(new Regular)), pixel_size_(1.0) {}












