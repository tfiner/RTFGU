// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


// This file contains the definition of the class BeveledBox

#include "BeveledBox.h"
#include "OpenCylinder.h"
#include "Rectangle.h"
#include "Sphere.h"
#include "Instance.h"

#include "Vector3D.h"
#include "Normal.h"


// ------------------------------------------------------------------------------ default constructor

BeveledBox::BeveledBox(void)
			:	Compound(),
				p0(-1.0),
				p1(1.0),
				rb(0.1),
				bbox(p0, p1)
{
	// edges
	// since the cylinders have to be defined initially in the vertical direction, it's easiest to use -(...)/2, +(...)/2 for
	// y0 and y1 in the constructors, and then rotate them about their centers.

	// top edges  (+ve y)

	Instance* top_front_edge = new Instance (new OpenCylinder(-(p1.x - p0.x - 2 * rb) / 2, (p1.x - p0.x - 2 * rb) / 2, rb));	// top front edge
	top_front_edge->rotate_z(90);
	top_front_edge->translate((p0.x + p1.x) / 2, p1.y - rb, p1.z - rb);
	top_front_edge->transform_texture(false);
	objects.push_back(top_front_edge);


	// top back (-ve z)

	Instance* top_back_edge = new Instance (new OpenCylinder(-(p1.x - p0.x - 2 * rb) / 2, (p1.x - p0.x - 2 * rb) / 2, rb));	// top back edge
	top_back_edge->rotate_z(90);
	top_back_edge->translate((p0.x + p1.x) / 2, p1.y - rb, p0.z + rb);
	top_back_edge->transform_texture(false);
	objects.push_back(top_back_edge);


	// top right (+ve x)

	Instance* top_right_edge = new Instance (new OpenCylinder(-(p1.z - p0.z - 2 * rb) / 2, (p1.z - p0.z - 2 * rb) / 2, rb)); // top right edge
	top_right_edge->rotate_x(90);
	top_right_edge->translate(p1.x - rb, p1.y - rb, (p0.z + p1.z) / 2);
	top_right_edge->transform_texture(false);
	objects.push_back(top_right_edge);


	// top left (-ve x)

	Instance* top_left_edge = new Instance (new OpenCylinder(-(p1.z - p0.z - 2 * rb) / 2, (p1.z - p0.z - 2 * rb) / 2, rb)); // top left edge
	top_left_edge->rotate_x(90);
	top_left_edge->translate(p0.x + rb, p1.y - rb, (p0.z + p1.z) / 2);
	top_left_edge->transform_texture(false);
	objects.push_back(top_left_edge);



	// bottom edges  (-ve y)

	// bottom front  (+ve z)

	Instance* bottom_front_edge = new Instance (new OpenCylinder(-(p1.x - p0.x - 2 * rb) / 2, (p1.x - p0.x - 2 * rb) / 2, rb));	// bottom fromt edge
	bottom_front_edge->rotate_z(90);
	bottom_front_edge->translate((p0.x + p1.x) / 2, p0.y + rb, p1.z - rb);
	bottom_front_edge->transform_texture(false);
	objects.push_back(bottom_front_edge);


	// bottom back  (-ve z)

	Instance* bottom_back_edge = new Instance (new OpenCylinder(-(p1.x - p0.x - 2 * rb) / 2, (p1.x - p0.x - 2 * rb) / 2, rb));	// bottom back edge
	bottom_back_edge->rotate_z(90);
	bottom_back_edge->translate((p0.x + p1.x) / 2, p0.y + rb, p0.z + rb);
	bottom_back_edge->transform_texture(false);
	objects.push_back(bottom_back_edge);


	// bottom right (-ve x, -ve y)

	Instance* bottom_right_edge = new Instance (new OpenCylinder(-(p1.z - p0.z - 2 * rb) / 2, (p1.z - p0.z - 2 * rb) / 2, rb)); // bottom right edge
	bottom_right_edge->rotate_x(90);
	bottom_right_edge->translate(p1.x - rb, p0.y + rb, (p0.z + p1.z) / 2);
	bottom_right_edge->transform_texture(false);
	objects.push_back(bottom_right_edge);

	// bottom left (-ve x, -ve y)

	Instance* bottom_left_edge = new Instance (new OpenCylinder(-(p1.z - p0.z - 2 * rb) / 2, (p1.z - p0.z - 2 * rb) / 2, rb)); // bottom left edge
	bottom_left_edge->rotate_x(90);
	bottom_left_edge->translate(p0.x + rb, p0.y + rb, (p0.z + p1.z) / 2);
	bottom_left_edge->transform_texture(false);
	objects.push_back(bottom_left_edge);


	// vertical edges

	// vertical right front  (+ve x, +ve z)

	Instance* vertical_right_front_edge = new Instance (new OpenCylinder(p0.y + rb, p1.y - rb, rb));
	vertical_right_front_edge->translate(p1.x - rb, 0, p1.z - rb);
	vertical_right_front_edge->transform_texture(false);
	objects.push_back(vertical_right_front_edge);

	// vertical left front  (-ve x, +ve z)

	Instance* vertical_left_front_edge = new Instance (new OpenCylinder(p0.y + rb, p1.y - rb, rb));
	vertical_left_front_edge->translate(p0.x + rb, 0, p1.z - rb);
	vertical_left_front_edge->transform_texture(false);
	objects.push_back(vertical_left_front_edge);

	// vertical left back  (-ve x, -ve z)

	Instance* vertical_left_back_edge = new Instance (new OpenCylinder(p0.y + rb, p1.y - rb, rb));
	vertical_left_back_edge->translate(p0.x + rb, 0, p0.z + rb);
	vertical_left_back_edge->transform_texture(false);
	objects.push_back(vertical_left_back_edge);


	// vertical right back  (+ve x, -ve z)

	Instance* vertical_right_back_edge = new Instance (new OpenCylinder(p0.y + rb, p1.y - rb, rb));
	vertical_right_back_edge->translate(p1.x - rb, 0, p0.z + rb);
	vertical_right_back_edge->transform_texture(false);
	objects.push_back(vertical_right_back_edge);



	// corner spheres

	// top right front

	Sphere* top_right_front_corner = new Sphere(Point3D(p1.x - rb, p1.y - rb, p1.z - rb), rb);
	objects.push_back(top_right_front_corner);

	// top left front  (-ve x)

	Sphere* top_left_front_corner = new Sphere(Point3D(p0.x + rb, p1.y - rb, p1.z - rb), rb);
	objects.push_back(top_left_front_corner);

	// top left back

	Sphere* top_left_back_corner = new Sphere(Point3D(p0.x + rb, p1.y - rb, p0.z + rb), rb);
	objects.push_back(top_left_back_corner);

	// top right back

	Sphere* top_right_back_corner = new Sphere(Point3D(p1.x - rb, p1.y - rb, p0.z + rb), rb);
	objects.push_back(top_right_back_corner);

	// bottom right front

	Sphere* bottom_right_front_corner = new Sphere(Point3D(p1.x - rb, p0.y + rb, p1.z - rb), rb);
	objects.push_back(bottom_right_front_corner);

	// bottom left front

	Sphere* bottom_left_front_corner = new Sphere(Point3D(p0.x + rb, p0.y + rb, p1.z - rb), rb);
	objects.push_back(bottom_left_front_corner);

	// bottom left back

	Sphere* bottom_left_back_corner = new Sphere(Point3D(p0.x + rb, p0.y + rb, p0.z + rb), rb);
	objects.push_back(bottom_left_back_corner);

	// bottom right back

	Sphere* bottom_right_back_corner = new Sphere(Point3D(p1.x - rb, p0.y + rb, p0.z + rb), rb);
	objects.push_back(bottom_right_back_corner);


	// the faces

	// bottom face: -ve y

	Rectangle* bottom_face	= new Rectangle(	Point3D(p0.x + rb, p0.y, p0.z + rb),
												Vector3D(0, 0, (p1.z - rb) - (p0.z + rb)),
												Vector3D((p1.x - rb) - (p0.x + rb), 0, 0),
												Normal(0, -1, 0));
	objects.push_back(bottom_face);


	// bottom face: +ve y

	Rectangle* top_face 	= new Rectangle(	Point3D(p0.x + rb, p1.y, p0.z + rb),
												Vector3D(0, 0, (p1.z - rb) - (p0.z + rb)),
												Vector3D((p1.x - rb) - (p0.x + rb), 0, 0),
												Normal(0, 1, 0));
	objects.push_back(top_face);


	// back face: -ve z

	Rectangle* back_face 	= new Rectangle(	Point3D(p0.x + rb, p0.y + rb, p0.z),
												Vector3D((p1.x - rb) - (p0.x + rb), 0, 0),
												Vector3D(0, (p1.y - rb) - (p0.y + rb), 0),
												Normal(0, 0 , -1));
	objects.push_back(back_face);


	// front face: +ve z

	Rectangle* front_face 	= new Rectangle(	Point3D(p0.x + rb, p0.y + rb, p1.z),
												Vector3D((p1.x - rb) - (p0.x + rb), 0, 0),
												Vector3D(0, (p1.y - rb) - (p0.y + rb), 0),
												Normal(0, 0 , 1));
	objects.push_back(front_face);


	// left face: -ve x

	Rectangle* left_face 	= new Rectangle(	Point3D(p0.x, p0.y + rb, p0.z + rb),
												Vector3D(0, 0, (p1.z - rb) - (p0.z + rb)),
												Vector3D(0, (p1.y - rb) - (p0.y + rb), 0),
												Normal(-1, 0 , 0));
	objects.push_back(left_face);


	// right face: +ve x

	Rectangle* right_face 	= new Rectangle(	Point3D(p1.x, p0.y + rb, p0.z + rb),
												Vector3D(0, 0, (p1.z - rb) - (p0.z + rb)),
												Vector3D(0, (p1.y - rb) - (p0.y + rb), 0),
												Normal(1, 0 , 0));
	objects.push_back(right_face);



}


// ------------------------------------------------------------------------------ constructor

BeveledBox::BeveledBox(	const Point3D& 	min_corner,
						const Point3D& 	max_corner,
						const double 	bevel_radius)
	: 	Compound(),
		p0(min_corner),
		p1(max_corner),
		rb(bevel_radius),
		bbox(p0, p1)
{

	// edges
	// since the cylinders have to be defined initially in the vertical direction, it's easiest to use -(...)/2, +(...)/2 for
	// y0 and y1 in the constructors, and then rotate them about their centers.

	// top edges  (+ve y)

	Instance* top_front_edge = new Instance (new OpenCylinder(-(p1.x - p0.x - 2 * rb) / 2, (p1.x - p0.x - 2 * rb) / 2, rb));	// top front edge
	top_front_edge->rotate_z(90);
	top_front_edge->translate((p0.x + p1.x) / 2, p1.y - rb, p1.z - rb);
	top_front_edge->transform_texture(false);
	objects.push_back(top_front_edge);


	// top back (-ve z)

	Instance* top_back_edge = new Instance (new OpenCylinder(-(p1.x - p0.x - 2 * rb) / 2, (p1.x - p0.x - 2 * rb) / 2, rb));	// top back edge
	top_back_edge->rotate_z(90);
	top_back_edge->translate((p0.x + p1.x) / 2, p1.y - rb, p0.z + rb);
	top_back_edge->transform_texture(false);
	objects.push_back(top_back_edge);


	// top right (+ve x)

	Instance* top_right_edge = new Instance (new OpenCylinder(-(p1.z - p0.z - 2 * rb) / 2, (p1.z - p0.z - 2 * rb) / 2, rb)); // top right edge
	top_right_edge->rotate_x(90);
	top_right_edge->translate(p1.x - rb, p1.y - rb, (p0.z + p1.z) / 2);
	top_right_edge->transform_texture(false);
	objects.push_back(top_right_edge);


	// top left (-ve x)

	Instance* top_left_edge = new Instance (new OpenCylinder(-(p1.z - p0.z - 2 * rb) / 2, (p1.z - p0.z - 2 * rb) / 2, rb)); // top left edge
	top_left_edge->rotate_x(90);
	top_left_edge->translate(p0.x + rb, p1.y - rb, (p0.z + p1.z) / 2);
	top_left_edge->transform_texture(false);
	objects.push_back(top_left_edge);



	// bottom edges  (-ve y)

	// bottom front  (+ve z)

	Instance* bottom_front_edge = new Instance (new OpenCylinder(-(p1.x - p0.x - 2 * rb) / 2, (p1.x - p0.x - 2 * rb) / 2, rb));	// bottom fromt edge
	bottom_front_edge->rotate_z(90);
	bottom_front_edge->translate((p0.x + p1.x) / 2, p0.y + rb, p1.z - rb);
	bottom_front_edge->transform_texture(false);
	objects.push_back(bottom_front_edge);


	// bottom back  (-ve z)

	Instance* bottom_back_edge = new Instance (new OpenCylinder(-(p1.x - p0.x - 2 * rb) / 2, (p1.x - p0.x - 2 * rb) / 2, rb));	// bottom back edge
	bottom_back_edge->rotate_z(90);
	bottom_back_edge->translate((p0.x + p1.x) / 2, p0.y + rb, p0.z + rb);
	bottom_back_edge->transform_texture(false);
	objects.push_back(bottom_back_edge);


	// bottom right (-ve x, -ve y)

	Instance* bottom_right_edge = new Instance (new OpenCylinder(-(p1.z - p0.z - 2 * rb) / 2, (p1.z - p0.z - 2 * rb) / 2, rb)); // bottom right edge
	bottom_right_edge->rotate_x(90);
	bottom_right_edge->translate(p1.x - rb, p0.y + rb, (p0.z + p1.z) / 2);
	bottom_right_edge->transform_texture(false);
	objects.push_back(bottom_right_edge);

	// bottom left (-ve x, -ve y)

	Instance* bottom_left_edge = new Instance (new OpenCylinder(-(p1.z - p0.z - 2 * rb) / 2, (p1.z - p0.z - 2 * rb) / 2, rb)); // bottom left edge
	bottom_left_edge->rotate_x(90);
	bottom_left_edge->translate(p0.x + rb, p0.y + rb, (p0.z + p1.z) / 2);
	bottom_left_edge->transform_texture(false);
	objects.push_back(bottom_left_edge);


	// vertical edges

	// vertical right front  (+ve x, +ve z)

	Instance* vertical_right_front_edge = new Instance (new OpenCylinder(p0.y + rb, p1.y - rb, rb));
	vertical_right_front_edge->translate(p1.x - rb, 0, p1.z - rb);
	vertical_right_front_edge->transform_texture(false);
	objects.push_back(vertical_right_front_edge);

	// vertical left front  (-ve x, +ve z)

	Instance* vertical_left_front_edge = new Instance (new OpenCylinder(p0.y + rb, p1.y - rb, rb));
	vertical_left_front_edge->translate(p0.x + rb, 0, p1.z - rb);
	vertical_left_front_edge->transform_texture(false);
	objects.push_back(vertical_left_front_edge);

	// vertical left back  (-ve x, -ve z)

	Instance* vertical_left_back_edge = new Instance (new OpenCylinder(p0.y + rb, p1.y - rb, rb));
	vertical_left_back_edge->translate(p0.x + rb, 0, p0.z + rb);
	vertical_left_back_edge->transform_texture(false);
	objects.push_back(vertical_left_back_edge);


	// vertical right back  (+ve x, -ve z)

	Instance* vertical_right_back_edge = new Instance (new OpenCylinder(p0.y + rb, p1.y - rb, rb));
	vertical_right_back_edge->translate(p1.x - rb, 0, p0.z + rb);
	vertical_right_back_edge->transform_texture(false);
	objects.push_back(vertical_right_back_edge);



	// corner spheres

	// top right front

	Sphere* top_right_front_corner = new Sphere(Point3D(p1.x - rb, p1.y - rb, p1.z - rb), rb);
	objects.push_back(top_right_front_corner);

	// top left front  (-ve x)

	Sphere* top_left_front_corner = new Sphere(Point3D(p0.x + rb, p1.y - rb, p1.z - rb), rb);
	objects.push_back(top_left_front_corner);

	// top left back

	Sphere* top_left_back_corner = new Sphere(Point3D(p0.x + rb, p1.y - rb, p0.z + rb), rb);
	objects.push_back(top_left_back_corner);

	// top right back

	Sphere* top_right_back_corner = new Sphere(Point3D(p1.x - rb, p1.y - rb, p0.z + rb), rb);
	objects.push_back(top_right_back_corner);

	// bottom right front

	Sphere* bottom_right_front_corner = new Sphere(Point3D(p1.x - rb, p0.y + rb, p1.z - rb), rb);
	objects.push_back(bottom_right_front_corner);

	// bottom left front

	Sphere* bottom_left_front_corner = new Sphere(Point3D(p0.x + rb, p0.y + rb, p1.z - rb), rb);
	objects.push_back(bottom_left_front_corner);

	// bottom left back

	Sphere* bottom_left_back_corner = new Sphere(Point3D(p0.x + rb, p0.y + rb, p0.z + rb), rb);
	objects.push_back(bottom_left_back_corner);

	// bottom right back

	Sphere* bottom_right_back_corner = new Sphere(Point3D(p1.x - rb, p0.y + rb, p0.z + rb), rb);
	objects.push_back(bottom_right_back_corner);


	// the faces

	// bottom face: -ve y

	Rectangle* bottom_face	= new Rectangle(	Point3D(p0.x + rb, p0.y, p0.z + rb),
												Vector3D(0, 0, (p1.z - rb) - (p0.z + rb)),
												Vector3D((p1.x - rb) - (p0.x + rb), 0, 0),
												Normal(0, -1, 0));
	objects.push_back(bottom_face);


	// bottom face: +ve y

	Rectangle* top_face 	= new Rectangle(	Point3D(p0.x + rb, p1.y, p0.z + rb),
												Vector3D(0, 0, (p1.z - rb) - (p0.z + rb)),
												Vector3D((p1.x - rb) - (p0.x + rb), 0, 0),
												Normal(0, 1, 0));
	objects.push_back(top_face);


	// back face: -ve z

	Rectangle* back_face 	= new Rectangle(	Point3D(p0.x + rb, p0.y + rb, p0.z),
												Vector3D((p1.x - rb) - (p0.x + rb), 0, 0),
												Vector3D(0, (p1.y - rb) - (p0.y + rb), 0),
												Normal(0, 0 , -1));
	objects.push_back(back_face);


	// front face: +ve z

	Rectangle* front_face 	= new Rectangle(	Point3D(p0.x + rb, p0.y + rb, p1.z),
												Vector3D((p1.x - rb) - (p0.x + rb), 0, 0),
												Vector3D(0, (p1.y - rb) - (p0.y + rb), 0),
												Normal(0, 0 , 1));
	objects.push_back(front_face);


	// left face: -ve x

	Rectangle* left_face 	= new Rectangle(	Point3D(p0.x, p0.y + rb, p0.z + rb),
												Vector3D(0, 0, (p1.z - rb) - (p0.z + rb)),
												Vector3D(0, (p1.y - rb) - (p0.y + rb), 0),
												Normal(-1, 0 , 0));
	objects.push_back(left_face);


	// right face: +ve x

	Rectangle* right_face 	= new Rectangle(	Point3D(p1.x, p0.y + rb, p0.z + rb),
												Vector3D(0, 0, (p1.z - rb) - (p0.z + rb)),
												Vector3D(0, (p1.y - rb) - (p0.y + rb), 0),
												Normal(1, 0 , 0));
	objects.push_back(right_face);
}

// ------------------------------------------------------------------------------ copy constructor

BeveledBox::BeveledBox (const BeveledBox& bb)
			: 	Compound(bb),
				p0(bb.p0),
				p1(bb.p1),
				rb(bb.rb),
				bbox(bb.bbox)
{}

// ------------------------------------------------------------------------------ clone

BeveledBox*
BeveledBox::clone(void) const {
	return(new BeveledBox(*this));
}


// ------------------------------------------------------------------------------ assignment operator

BeveledBox&
BeveledBox::operator= (const BeveledBox& rhs)
{
	if (this == &rhs)
		return (*this);

	Compound::operator=(rhs);

	p0		= rhs.p0;
	p1		= rhs.p1;
	rb		= rhs.rb;
	bbox	= rhs.bbox;

	return (*this) ;
}


// ------------------------------------------------------------------------------ destructor

BeveledBox::~BeveledBox (void) {}



BBox
BeveledBox::get_bounding_box(void) {
	return(bbox);
}


// ------------------------------------------------------------------------------ shadow_hit

bool
BeveledBox::shadow_hit(const Ray& ray, double& tmin) const {
    return false;
/*
	if (bbox.hit(ray))
		return (Compound::shadow_hit(ray, tmin));
	else
		return (false);
*/
}


// ------------------------------------------------------------------------------ hit

bool
BeveledBox::hit(const Ray& ray, double& tmin, ShadeRec& sr) const {
	if (bbox.hit(ray))
		return (Compound::hit(ray, tmin, sr));
	else
		return (false);
}





