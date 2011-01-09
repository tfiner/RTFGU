#if 0 // pending delete.

// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

#include <algorithm>   // for random_shuffle in Sampler::setup_shuffled_indices

#include "Constants.h"
#include "Sampler.h"

#include <vector>
#include <cassert>


using std::vector;


namespace {
    const int DEFAULT_NUM_SETS = 83;
}


Sampler::Sampler() {
    init(1, DEFAULT_NUM_SETS);
}


Sampler::Sampler(const int ns) {
    init(ns, DEFAULT_NUM_SETS);
}


Sampler::Sampler(const int ns, const int n_sets) {
    init(ns, n_sets);
}


Sampler::Sampler(const Sampler& s)
        : 	num_samples(s.num_samples),
        num_sets(s.num_sets),
        samples(s.samples),
        shuffled_indices(s.shuffled_indices),
//        disk_samples(s.disk_samples),
//        hemisphere_samples(s.hemisphere_samples),
//        sphere_samples(s.sphere_samples),
        count(s.count),
        jump(s.jump) {}



Sampler& Sampler::operator= (const Sampler& rhs) {
    if (this == &rhs)
        return (*this);

    num_samples 		= rhs.num_samples;
    num_sets			= rhs.num_sets;
    samples				= rhs.samples;
    shuffled_indices	= rhs.shuffled_indices;
//    disk_samples		= rhs.disk_samples;
//    hemisphere_samples	= rhs.hemisphere_samples;
//    sphere_samples		= rhs.sphere_samples;
    count				= rhs.count;
    jump				= rhs.jump;

    return *this;
}


Sampler::~Sampler() {}


void Sampler::init(int num_samples, int num_sets) {
    this->num_samples   = num_samples;
    this->num_sets      = num_sets;
    samples.reserve(num_samples * num_sets);
    setup_shuffled_indices();
    count = 0;
    jump = 0;
}


int Sampler::get_num_samples() {
    return num_samples;
}

std::vector<Point2D> Sampler::get_samples() const {
    return samples;
}


// shuffle the x coordinates of the points within each set
void Sampler::shuffle_x_coordinates() {
    for (int p = 0; p < num_sets; p++) {
        for (int i = 0; i <  num_samples - 1; i++) {
            int target = rand_int() % num_samples + p * num_samples;
            float temp = samples[i + p * num_samples + 1].x;
            samples[i + p * num_samples + 1].x = samples[target].x;
            samples[target].x = temp;
        }
    }
}


// shuffle the y coordinates of the points within set
void Sampler::shuffle_y_coordinates() {
    for (int p = 0; p < num_sets; p++) {
        for (int i = 0; i <  num_samples - 1; i++) {
            int target = rand_int() % num_samples + p * num_samples;
            float temp = samples[i + p * num_samples + 1].y;
            samples[i + p * num_samples + 1].y = samples[target].y;
            samples[target].y = temp;
        }
    }
}



// sets up randomly shuffled indices for the samples array
void Sampler::setup_shuffled_indices() {
    shuffled_indices.reserve(num_samples * num_sets);
    vector<int> indices;

    for (int j = 0; j < num_samples; j++)
        indices.push_back(j);

    for (int p = 0; p < num_sets; p++) {
        random_shuffle(indices.begin(), indices.end());

        for (int j = 0; j < num_samples; j++)
            shuffled_indices.push_back(indices[j]);
    }
}



// Maps the 2D sample points in the square [-1,1] X [-1,1] to a unit disk, using Peter Shirley's
// concentric map function
/*
void Sampler::map_samples_to_unit_disk() {
    int size = samples.size();
    float r, phi;		// polar coordinates
    Point2D sp; 		// sample point on unit disk

    disk_samples.reserve(size);

    for (int j = 0; j < size; j++) {
        // map sample point to [-1, 1] X [-1,1]

        sp.x = 2.0 * samples[j].x - 1.0;
        sp.y = 2.0 * samples[j].y - 1.0;

        if (sp.x > -sp.y) {			// sectors 1 and 2
            if (sp.x > sp.y) {		// sector 1
                r = sp.x;
                phi = sp.y / sp.x;
            } else {					// sector 2
                r = sp.y;
                phi = 2 - sp.x / sp.y;
            }
        } else {						// sectors 3 and 4
            if (sp.x < sp.y) {		// sector 3
                r = -sp.x;
                phi = 4 + sp.y / sp.x;
            } else {					// sector 4
                r = -sp.y;
                if (sp.y != 0.0)	// avoid division by zero at origin
                    phi = 6 - sp.x / sp.y;
                else
                    phi  = 0.0;
            }
        }

        phi *= PI / 4.0;

        disk_samples[j].x = r * cos(phi);
        disk_samples[j].y = r * sin(phi);
    }

    samples.erase(samples.begin(), samples.end());
}
*/


// Maps the 2D sample points to 3D points on a unit hemisphere with a cosine power
// density distribution in the polar angle
void Sampler::map_samples_to_hemisphere(const float exp) {
    assert(!"refacor into geometric policy");
//    int size = samples.size();
//    hemisphere_samples.reserve(num_samples * num_sets);
//
//    for (int j = 0; j < size; j++) {
//        float cos_phi = cos(2.0 * PI * samples[j].x);
//        float sin_phi = sin(2.0 * PI * samples[j].x);
//        float cos_theta = pow((1.0 - samples[j].y), 1.0 / (exp + 1.0));
//        float sin_theta = sqrt (1.0 - cos_theta * cos_theta);
//        float pu = sin_theta * cos_phi;
//        float pv = sin_theta * sin_phi;
//        float pw = cos_theta;
//        hemisphere_samples.push_back(Point3D(pu, pv, pw));
//    }
}


// Maps the 2D sample points to 3D points on a unit sphere with a uniform density
// distribution over the surface
// this is used for modelling a spherical light
//void Sampler::map_samples_to_sphere() {
//    float r1, r2;
//    float x, y, z;
//    float r, phi;
//
//    sphere_samples.reserve(num_samples * num_sets);
//
//    for (int j = 0; j < num_samples * num_sets; j++) {
//        r1 	= samples[j].x;
//        r2 	= samples[j].y;
//        z 	= 1.0 - 2.0 * r1;
//        r 	= sqrt(1.0 - z * z);
//        phi = TWO_PI * r2;
//        x 	= r * cos(phi);
//        y 	= r * sin(phi);
//        sphere_samples.push_back(Point3D(x, y, z));
//    }
//}


// the final version in Listing 5.13
Point2D Sampler::sample_unit_square() {
    return next_sample2D(samples);
}



/*
// the first revised version in Listing in Listing 5.8
Point2D Sampler::sample_unit_square() {
	if (count % num_samples == 0)  									// start of a new pixel
		jump = (rand_int() % num_sets) * num_samples;				// random index jump initialised to zero in constructor

	return (samples[jump + count++ % num_samples]);
}

// the original version in Listing 5.7
Point2D Sampler::sample_unit_square() {
	return (samples[count++ % (num_samples * num_sets)]);
}


Point2D Sampler::sample_unit_disk() {
    return next_sample2D(disk_samples);
}
*/


Point3D Sampler::sample_hemisphere() {
    assert(!"Refactor into a policy");
//    return next_sample3D(hemisphere_samples);
    return Point3D();
}


//Point3D Sampler::sample_sphere() {
//    return next_sample3D(sphere_samples);
//}


Point2D Sampler::next_sample2D(const std::vector<Point2D>& samples2D) {
    // start of a new pixel
    // random index jump initialised to zero in init()
    if (count % num_samples == 0)
        jump = (rand_int() % num_sets) * num_samples;

    return samples2D[jump + shuffled_indices[jump + count++ % num_samples]];
}

Point3D Sampler::next_sample3D(const std::vector<Point3D>& samples3D) {
    // start of a new pixel
    if (count % num_samples == 0)  									// start of a new pixel
        jump = (rand_int() % num_sets) * num_samples;

    return samples3D[jump + shuffled_indices[jump + count++ % num_samples]];
}


// This is a specialised function called in LatticeNoise::init_vector_table
// It doesn't shuffle the indices
//Point2D Sampler::sample_one_set() {
//    return(samples[count++ % num_samples]);
//}

#endif//
