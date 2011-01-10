#ifndef __VIEW_PLANE__
#define __VIEW_PLANE__

#include "SampleGenerator.h"


#include <boost/shared_ptr.hpp>


typedef boost::shared_ptr< SampleGenerator2D > SamplerPtr;


class ViewPlane {
public:
    int 			hres;   					// horizontal image resolution
    int 			vres;   					// vertical image resolution
    float			gamma;						// gamma correction factor
    float			inv_gamma;					// the inverse of the gamma correction factor
    bool			show_out_of_gamut;			// display red if RGBColor out of gamut


    ViewPlane();

    void set_hres(const int h_res);
    void set_vres(const int v_res);

    float get_pixel_size() const { return pixel_size_; }
    void set_pixel_size(const float size);

    void set_gamma(const float g);
    void set_gamut_display(const bool show);
    void set_sampler( SamplerPtr sampler );
    SamplerPtr get_sampler();

private:
    SamplerPtr  sampler_;
    float	    pixel_size_;
};


inline void
ViewPlane::set_hres(const int h_res) {
    hres = h_res;
}


inline void ViewPlane::set_vres(const int v_res) {
    vres = v_res;
}


inline void ViewPlane::set_pixel_size(const float size) {
    pixel_size_ = size;
}


inline void ViewPlane::set_gamma(const float g) {
    gamma = g;
    inv_gamma = 1.0 / gamma;
}


inline void ViewPlane::set_gamut_display(const bool show) {
    show_out_of_gamut = show;
}


inline void ViewPlane::set_sampler( SamplerPtr sampler ) {
    sampler_ = sampler;
}

inline SamplerPtr ViewPlane::get_sampler() {
    return sampler_;
}


#endif
