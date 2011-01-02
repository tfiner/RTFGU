#if 0
// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


// This file contains the definition of the class BeveledWedge
// A BeveledWedge is build from a number of primitives as listed in the #includes below
// There is code on the website for Instance, OpenCylinder, and Sphere
// You will have to implement the other objects

#include "BeveledWedge.h"

#include "Constants.h"

#include "Annulus.h"
#include "ConcavePartCylinder.h"
#include "ConvexPartCylinder.h"
#include "ConvexPartTorus.h"
#include "Instance.h"
#include "OpenCylinder.h"
#include "PartAnnulus.h"
#include "Rectangle.h"
#include "Sphere.h"

// ------------------------------------------------------------------------------ constructor

BeveledWedge::BeveledWedge(	const double _y0,		// minimum y value
                            const double _y1,		// minimum y value
                            const double _r0,		// inner radius
                            const double _r1,		// outer radius
                            const double _rb,		// bevel radius
                            const double _phi0,		// minimum azimuth angle in degrees
                            const double _phi1)		// maximum azimuth angle in degrees

        :	y0(_y0),
        y1(_y1),
        r0(_r0),
        r1(_r1),
        rb(_rb),
        phi0(_phi0),
        phi1(_phi1) {
    double sin_phi0 = sin(phi0 * PI_ON_180);  // in radians
    double cos_phi0 = cos(phi0 * PI_ON_180);  // in radians
    double sin_phi1 = sin(phi1 * PI_ON_180);  // in radians
    double cos_phi1 = cos(phi1 * PI_ON_180);  // in radians

    double sin_alpha = rb / (r0 + rb);
    double cos_alpha = sqrt(r0 * r0 + 2.0 * r0 * rb) / (r0 + rb);
    double sin_beta = rb / (r1 - rb);
    double cos_beta = sqrt(r1 * r1 - 2.0 * r1 * rb) / (r1 - rb);

    double xc1 = (r0 + rb) * (sin_phi0 * cos_alpha + cos_phi0 * sin_alpha);
    double zc1 = (r0 + rb) * (cos_phi0 * cos_alpha - sin_phi0 * sin_alpha);

    double xc2 = (r1 - rb) * (sin_phi0 * cos_beta + cos_phi0 * sin_beta);
    double zc2 = (r1 - rb) * (cos_phi0 * cos_beta - sin_phi0 * sin_beta);

    double xc3 = (r0 + rb) * (sin_phi1 * cos_alpha - cos_phi1 * sin_alpha);
    double zc3 = (r0 + rb) * (cos_phi1 * cos_alpha + sin_phi1 * sin_alpha);

    double xc4 = (r1 - rb) * (sin_phi1 * cos_beta - cos_phi1 * sin_beta);
    double zc4 = (r1 - rb) * (cos_phi1 * cos_beta + sin_phi1 * sin_beta);


    // corner spheres -------------------------------------------------------------------------------

    // bottom spheres

    Sphere* bottom_c1 = new Sphere(Point3D(xc1, y0 + rb, zc1), rb);
    objects.push_back(bottom_c1);

    Sphere* bottom_c2 = new Sphere(Point3D(xc2, y0 + rb, zc2), rb);
    objects.push_back(bottom_c2);

    Sphere* bottom_c3 = new Sphere(Point3D(xc3, y0 + rb, zc3), rb);
    objects.push_back(bottom_c3);

    Sphere* bottom_c4 = new Sphere(Point3D(xc4, y0 + rb, zc4), rb);
    objects.push_back(bottom_c4);


    // top spheres

    Sphere* top_c1 = new Sphere(Point3D(xc1, y1 - rb, zc1), rb);
    objects.push_back(top_c1);

    Sphere* top_c2 = new Sphere(Point3D(xc2, y1 - rb, zc2), rb);
    objects.push_back(top_c2);

    Sphere* top_c3 = new Sphere(Point3D(xc3, y1 - rb, zc3), rb);
    objects.push_back(top_c3);

    Sphere* top_c4 = new Sphere(Point3D(xc4, y1 - rb, zc4), rb);
    objects.push_back(top_c4);


    // vertical cylinders ------------------------------------------------------------------------------

    Instance* bottom_c1_cylinder = new Instance(new OpenCylinder(y0 + rb, y1 - rb, rb));
    bottom_c1_cylinder->translate(xc1, 0.0, zc1);
    bottom_c1_cylinder->transform_texture(false);
    objects.push_back(bottom_c1_cylinder);

    Instance* bottom_c2_cylinder = new Instance(new OpenCylinder(y0 + rb, y1 - rb, rb));
    bottom_c2_cylinder->translate(xc2, 0.0, zc2);
    bottom_c2_cylinder->transform_texture(false);
    objects.push_back(bottom_c2_cylinder);

    Instance* bottom_c3_cylinder = new Instance(new OpenCylinder(y0 + rb, y1 - rb, rb));
    bottom_c3_cylinder->translate(xc3, 0.0, zc3);
    bottom_c3_cylinder->transform_texture(false);
    objects.push_back(bottom_c3_cylinder);

    Instance* bottom_c4_cylinder = new Instance(new OpenCylinder(y0 + rb, y1 - rb, rb));
    bottom_c4_cylinder->translate(xc4, 0.0, zc4);
    bottom_c4_cylinder->transform_texture(false);
    objects.push_back(bottom_c4_cylinder);


    // inner curved surface ---------------------------------------------------------------------------------

    // the azimuth angle range has to be specified in degrees

    double alpha = acos(cos_alpha);  // radians
    double phi_min = phi0 + alpha * 180.0 / PI;
    double phi_max = phi1 - alpha * 180.0 / PI;

    ConcavePartCylinder* inner_cylinder_ptr = new ConcavePartCylinder(y0 + rb, y1 - rb, r0, phi_min, phi_max);
    objects.push_back(inner_cylinder_ptr);


    // outer curved surface -----------------------------------------------------------------------------------

    // the azimuth angle range has to be specified in degrees

    double beta = acos(cos_beta);  // radians
    phi_min = phi0 + beta * 180.0 / PI;
    phi_max = phi1 - beta * 180.0 / PI;

    ConvexPartCylinder* outer_cylinder_ptr = new ConvexPartCylinder(y0 + rb, y1 - rb, r1, phi_min, phi_max);
    objects.push_back(outer_cylinder_ptr);


    // phi0 vertical rectangle

    double s1 = sqrt(r0 * r0 + 2.0 * r0 * rb);
    double s2 = sqrt(r1 * r1 - 2.0 * r1 * rb);
    Point3D p1(s1 * sin_phi0, y0 + rb, s1 * cos_phi0);
    Point3D p2(s2 * sin_phi0, y0 + rb, s2 * cos_phi0);
    Vector3D a = p2 - p1;
    Vector3D b(0, y1 - y0 - 2.0 * rb, 0);

    Rectangle* phi0_rectangle_ptr = new Rectangle(p1, a, b);
    objects.push_back(phi0_rectangle_ptr);


    // phi1 vertical rectangle

    Point3D p3(s1 * sin_phi1, y0 + rb, s1 * cos_phi1);
    Point3D p4(s2 * sin_phi1, y0 + rb, s2 * cos_phi1);
    a = p3 - p4;

    Rectangle* phi1_rectangle_ptr = new Rectangle(p4, a, b);
    objects.push_back(phi1_rectangle_ptr);



    // the tori --------------------------------------------------------------------------------------------

    // inner bottom

    phi_min = phi0 + alpha * 180.0 / PI;
    phi_max = phi1 - alpha * 180.0 / PI;

    Instance* inner_bottom_torus = new Instance(new ConvexPartTorus(r0 + rb, rb, phi_min, phi_max, 0, 360));
    inner_bottom_torus->translate(0.0, y0 + rb, 0.0);
    inner_bottom_torus->transform_texture(false);
    objects.push_back(inner_bottom_torus);


    // inner top

    Instance* inner_top_torus = new Instance(new ConvexPartTorus(r0 + rb, rb, phi_min, phi_max, 0, 360));
    inner_top_torus->translate(0.0, y1 - rb, 0.0);
    inner_top_torus->transform_texture(false);
    objects.push_back(inner_top_torus);


    // outer bottom

    phi_min = phi0 + beta * 180.0 / PI;
    phi_max = phi1 - beta * 180.0 / PI;

    Instance* outer_bottom_torus = new Instance(new ConvexPartTorus(r1 - rb, rb, phi_min, phi_max, 0, 360));
    outer_bottom_torus->translate(0.0, y0 + rb, 0.0);
    outer_bottom_torus->transform_texture(false);
    objects.push_back(outer_bottom_torus);


    // outer top

    Instance* outer_top_torus = new Instance(new ConvexPartTorus(r1 - rb, rb, phi_min, phi_max, 0, 360));
    outer_top_torus->translate(0.0, y1 - rb, 0.0);
    outer_top_torus->transform_texture(false);
    objects.push_back(outer_top_torus);


    // horizontal cylinders ----------------------------------------------------------------------------------

    // phi0 bottom cylinder

    Instance* phi0_bottom_cylinder_ptr = new Instance(new OpenCylinder(0, s2 - s1, rb));
    phi0_bottom_cylinder_ptr->rotate_x(90);
    phi0_bottom_cylinder_ptr->rotate_y(phi0);
    phi0_bottom_cylinder_ptr->translate(xc1, y0 + rb, zc1);
    phi0_bottom_cylinder_ptr->transform_texture(false);
    objects.push_back(phi0_bottom_cylinder_ptr);


    // phi0 top cylinder

    Instance* phi0_top_cylinder_ptr = new Instance(new OpenCylinder(0, s2 - s1, rb));
    phi0_top_cylinder_ptr->rotate_x(90);
    phi0_top_cylinder_ptr->rotate_y(phi0);
    phi0_top_cylinder_ptr->translate(xc1, y1 - rb, zc1);
    phi0_top_cylinder_ptr->transform_texture(false);
    objects.push_back(phi0_top_cylinder_ptr);


    // phi1 bottom cylinder

    Instance* phi1_bottom_cylinder_ptr = new Instance(new OpenCylinder(0, s2 - s1, rb));
    phi1_bottom_cylinder_ptr->rotate_x(90);
    phi1_bottom_cylinder_ptr->rotate_y(phi1);
    phi1_bottom_cylinder_ptr->translate(xc3, y0 + rb, zc3);
    phi1_bottom_cylinder_ptr->transform_texture(false);
    objects.push_back(phi1_bottom_cylinder_ptr);


    // phi1 top cylinder

    Instance* phi1_top_cylinder_ptr = new Instance(new OpenCylinder(0, s2 - s1, rb));
    phi1_top_cylinder_ptr->rotate_x(90);
    phi1_top_cylinder_ptr->rotate_y(phi1);
    phi1_top_cylinder_ptr->translate(xc3, y1 - rb, zc3);
    phi1_top_cylinder_ptr->transform_texture(false);
    objects.push_back(phi1_top_cylinder_ptr);


    // top flat surface -----------------------------------------------------------------------------------

    // main part

    Point3D center(0, y1, 0);
    Normal normal(0, 1, 0);
    double r_min = r0 + rb;
    double r_max = r1 - rb;
    phi_min = phi0 + alpha * 180.0 / PI;
    phi_max = phi1 - alpha * 180.0 / PI;

    PartAnnulus* top_main_part_ptr = new PartAnnulus(center, normal, r_min, r_max, phi_min, phi_max);
    objects.push_back(top_main_part_ptr);


    // small phi0 side patch

    r_min = 0.0;
    r_max = s2 - s1;
    phi_min = 0.0;
    phi_max = alpha * 180.0 / PI;

    Instance* top_phi0_patch_ptr = new Instance(new PartAnnulus(center, normal, r_min, r_max, phi_min, phi_max));
    top_phi0_patch_ptr->rotate_y(phi0);
    top_phi0_patch_ptr->translate(xc1, 0.0, zc1);
    top_phi0_patch_ptr->transform_texture(false);
    objects.push_back(top_phi0_patch_ptr);


    // small phi1 side patch

    phi_min = 360.0 - alpha * 180.0 / PI;
    phi_max = 360.0;

    Instance* top_phi1_patch_ptr = new Instance(new PartAnnulus(center, normal, r_min, r_max, phi_min, phi_max));
    top_phi1_patch_ptr->rotate_y(phi1);
    top_phi1_patch_ptr->translate(xc3, 0.0, zc3);
    top_phi1_patch_ptr->transform_texture(false);
    objects.push_back(top_phi1_patch_ptr);



    // bottom flat surface ---------------------------------------------------------------------------------

    // main part

    center = Point3D(0, y0, 0);
    normal = Normal(0, -1, 0);
    r_min = r0 + rb;
    r_max = r1 - rb;
    phi_min = phi0 + alpha * 180.0 / PI;
    phi_max = phi1 - alpha * 180.0 / PI;

    PartAnnulus* bottom_main_part_ptr = new PartAnnulus(center, normal, r_min, r_max, phi_min, phi_max);
    objects.push_back(bottom_main_part_ptr);


    // small phi0 side patch

    r_min = 0.0;
    r_max = s2 - s1;
    phi_min = 0.0;
    phi_max = alpha * 180.0 / PI;

    Instance* bottom_phi0_patch_ptr = new Instance(new PartAnnulus(center, normal, r_min, r_max, phi_min, phi_max));
    bottom_phi0_patch_ptr->rotate_y(phi0);
    bottom_phi0_patch_ptr->translate(xc1, 0.0, zc1);
    bottom_phi0_patch_ptr->transform_texture(false);
    objects.push_back(bottom_phi0_patch_ptr);


    // small phi1 side patch

    phi_min = 360.0 - alpha * 180.0 / PI;
    phi_max = 360.0;

    Instance* bottom_phi1_patch_ptr = new Instance(new PartAnnulus(center, normal, r_min, r_max, phi_min, phi_max));
    bottom_phi1_patch_ptr->rotate_y(phi1);
    bottom_phi1_patch_ptr->translate(xc3, 0.0, zc3);
    bottom_phi1_patch_ptr->transform_texture(false);
    objects.push_back(bottom_phi1_patch_ptr);



    // compute the bounding box

    double x[4] = {xc1, xc2, xc3, xc4};
    double z[4] = {zc1, zc2, zc3, zc4};


    // first, assume that the wedge is completely inside a quadrant, which will be true for most wedges

    // work out the maximum and minimum values

    double x0 = kHugeValue;
    double z0 = kHugeValue;

    for (int j = 0; j <= 3; j++)  {
        if (x[j] < x0)
            x0 = x[j];
    }

    for (int j = 0; j <= 3; j++) {
        if (z[j] < z0)
            z0 = z[j];
    }

    double x1 = -kHugeValue;
    double z1 = -kHugeValue;

    for (int j = 0; j <= 3; j++) {
        if (x[j] > x1)
            x1 = x[j];
    }

    for (int j = 0; j <= 3; j++) {
        if (z[j] > z1)
            z1 = z[j];
    }

    // assign values to the bounding box

    bbox.x0 = x0 - rb;
    bbox.y0 = y0;
    bbox.z0 = z0 - rb;
    bbox.x1 = x1 + rb;
    bbox.y1 = y1;
    bbox.z1 = z1 + rb;

    bool spans90 = phi0 < 90 and phi1 > 90;
    bool spans180 = phi0 < 180 and phi1 > 180;
    bool spans270 = phi0 < 270 and phi1 > 270;

    if (spans90 && spans180 && spans270) {
        bbox.x0 = -r1;
        bbox.z0 = -r1;
        bbox.x1 = r1;
        bbox.z1 = max(zc2, zc4);
    } else if (spans90 && spans180) {
        bbox.x0 = xc4 - rb;
        bbox.z0 = -r1;
        bbox.x1 = r1;
        bbox.z1 = zc2 + rb;
    } else if (spans180 && spans270) {
        bbox.x0 = -r1;
        bbox.z0 = -r1;
        bbox.x1 = xc2 + rb;
        bbox.z1 = zc4 + rb;
    } else if (spans90) {
        bbox.x0 = min(xc1, xc3);
        bbox.z0 = zc4 - rb;
        bbox.x1 = r1;
        bbox.z1 = zc2 + rb;
    } else if (spans180) {
        bbox.x0 = xc4 - rb;
        bbox.z0 = -r1;
        bbox.x1 = xc2 + rb;
        bbox.z1 = max(zc1, zc3);
    } else if (spans270) {
        bbox.x0 = -r1;
        bbox.z0 = zc2 - rb;
        bbox.x1 = max(xc1, xc3);
        bbox.z1 = zc4 + rb;
    }
}




// ------------------------------------------------------------------------------ copy constructor

BeveledWedge::BeveledWedge (const BeveledWedge& bw)
        : 	Compound(bw),
        y0(bw.y0),
        y1(bw.y1),
        r0(bw.r0),
        r1(bw.r1),
        rb(bw.rb),
        phi0(bw.phi0),
        phi1(bw.phi1),
        bbox(bw.bbox) {}

// ------------------------------------------------------------------------------ clone

BeveledWedge*
BeveledWedge::clone (void) const {
    return(new BeveledWedge(*this));
}


// ------------------------------------------------------------------------------ assignment operator

BeveledWedge&
BeveledWedge::operator= (const BeveledWedge& rhs) {
    if (this == &rhs)
        return (*this);

    Compound::operator=(rhs);

    y0 		= rhs.y0;
    y1 		= rhs.y1;
    r0 		= rhs.r0;
    r1 		= rhs.r1;
    rb 		= rhs.rb;
    phi0 	= rhs.phi0;
    phi1 	= rhs.phi1;
    bbox	= rhs.bbox;

    return (*this) ;
}


// ------------------------------------------------------------------------------ destructor

BeveledWedge::~BeveledWedge(void) {}



// ------------------------------------------------------------------------------ get_bounding_box

BBox
BeveledWedge::get_bounding_box(void) {
    return (bbox);
}



// ------------------------------------------------------------------------------ hit

bool
BeveledWedge::hit(const Ray& ray, double& tmin, ShadeRec& sr) const {
    if (bbox.hit(ray))
        return (Compound::hit(ray, tmin, sr));
    else
        return (false);
}

#endif
