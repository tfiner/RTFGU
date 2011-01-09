#ifndef __SAMPLER__
#define __SAMPLER__


// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


#include <vector>
#include <math.h>

#include "Point2D.h"
#include "Point3D.h"
#include "Maths.h"

class Sampler {
public:
    Sampler();
    Sampler(const int num);
    Sampler(const int num, const int num_sets);
    Sampler(const Sampler& s);

    Sampler& operator= (const Sampler& rhs);

    virtual Sampler* clone() const = 0;

    virtual ~Sampler();

    void init(int num_samples, int num_sets);

    // generate sample patterns in a unit square
    virtual void generate_samples() = 0;
    int get_num_samples();
    std::vector<Point2D> get_samples() const;

    void shuffle_x_coordinates();
    void shuffle_y_coordinates();
    void setup_shuffled_indices();

//    void map_samples_to_unit_disk();
    void map_samples_to_hemisphere(const float p);
//    void map_samples_to_sphere();

    // the following functions are not const because they change count and jump
    virtual Point2D sample_unit_square();

//    Point2D	sample_unit_disk();
    Point3D	sample_hemisphere();
//    Point3D	sample_sphere();
//    Point2D	sample_one_set();
    // this is not discussed in the book, but see the
    // file LatticeNoise.cpp in Chapter 31

protected:
    int 					num_samples;     		// the number of sample points in a set
    int 					num_sets;				// the number of sample sets
    std::vector<Point2D>	samples;				// sample points on a unit square
    std::vector<int>		shuffled_indices;		// shuffled samples array indices
//    std::vector<Point2D>	disk_samples;			// sample points on a unit disk
//    std::vector<Point3D> 	hemisphere_samples;		// sample points on a unit hemisphere
//    std::vector<Point3D>    sphere_samples;			// sample points on a unit sphere
    unsigned long 			count;					// the current number of sample points used
    int 					jump;					// random index jump

private:
    Point2D next_sample2D(const std::vector<Point2D>& points);
    Point3D next_sample3D(const std::vector<Point3D>& points);

};

#endif

