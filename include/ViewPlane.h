#ifndef __VIEW_PLANE__
#define __VIEW_PLANE__

#include <boost/shared_ptr.hpp>


class Sampler;
typedef boost::shared_ptr<Sampler> SamplerPtr;


class ViewPlane {
public:
    int 			hres;   					// horizontal image resolution
    int 			vres;   					// vertical image resolution
    float			gamma;						// gamma correction factor
    float			inv_gamma;					// the inverse of the gamma correction factor
    bool			show_out_of_gamut;			// display red if RGBColor out of gamut



public:

    ViewPlane();   								// default Constructor
    ~ViewPlane();   							// destructor

    void set_hres(const int h_res);

    void set_vres(const int v_res);

    float get_pixel_size() const { return s; }
    void set_pixel_size(const float size);

    void set_gamma(const float g);

    void set_gamut_display(const bool show);

    void set_sampler( SamplerPtr sampler );

    SamplerPtr get_sampler();

private:
    SamplerPtr  sampler_;
    float	    s;							// pixel size
};




// ------------------------------------------------------------------------------ set_hres

inline void
ViewPlane::set_hres(const int h_res) {
    hres = h_res;
}


// ------------------------------------------------------------------------------ set_vres

inline void
ViewPlane::set_vres(const int v_res) {
    vres = v_res;
}


// ------------------------------------------------------------------------------ set_pixel_size

inline void
ViewPlane::set_pixel_size(const float size) {
    s = size;
}


// ------------------------------------------------------------------------------ set_gamma

inline void
ViewPlane::set_gamma(const float g) {
    gamma = g;
    inv_gamma = 1.0 / gamma;
}


// ------------------------------------------------------------------------------ set_gamut_display

inline void
ViewPlane::set_gamut_display(const bool show) {
    show_out_of_gamut = show;
}



//inline void
//ViewPlane::set_samples(const int n) {
//    num_samples = n;
//}


inline void ViewPlane::set_sampler( SamplerPtr sampler ) {
    sampler_ = sampler;
}

inline SamplerPtr ViewPlane::get_sampler() {
    return sampler_;
}


#endif
