#ifndef __WORLD__
#define __WORLD__


// This file contains the declaration of the class World
// The World class does not have a copy constructor or an assignment operator, for the followign reasons:

// 1 	There's no need to copy construct or assign the World
// 2 	We wouldn't want to do this anyway, because the world can contain an arbitray amount of data
// 3 	These operations wouldn't work because the world is self-referencing:
//	 	the Tracer base class contains a pointer to the world. If we wrote a correct copy constructor for the
// 	  	Tracer class, the World copy construtor would call itself recursively until we ran out of memory.


#include <vector>

#include "ViewPlane.h"
#include "RGBColor.h"
#include "GeometricObject.h"
#include "Sphere.h"
#include "Ray.h"
#include "SingleSphere.h"

#include "Camera.h"
#include "Light.h"
#include "Ambient.h"

#include <boost/smart_ptr.hpp>

using namespace std;

class RenderThread; 	//part of skeleton - wxRaytracer.h

class IRenderer;
typedef boost::shared_ptr<IRenderer> RendererPtr;

class Tracer;
typedef boost::shared_ptr<Tracer> TracerPtr;

typedef vector<GeometricObject*> Objects;

class World {
public:
    World();
    ~World();

    void set_renderer(RendererPtr renderer);
    void set_tracer(TracerPtr tracer);

    void add_object(GeometricObject* object_ptr);
    void add_light(Light* light_ptr);
    void set_ambient_light(Light* light_ptr);
    void set_camera(Camera* c_ptr);

    void render_scene();
    RGBColor max_to_one(const RGBColor& c) const;
    RGBColor clamp_to_color(const RGBColor& c) const;
    void display_pixel(const int row, const int column, const RGBColor& pixel_color) const;

    ShadeRec hit_objects(const Ray& ray);
    ShadeRec hit_bare_bones_objects(const Ray& ray) const;

    void set_ambient(Light* light) {
        ambient_ptr = light;
    }

    Light* get_ambient() const {
        return ambient_ptr;
    }
    const vector<Light*>& get_lights() const {
        return lights;
    }

    void set_background(RGBColor color) {
        background_color = color;
    }

    RGBColor get_background() const {
        return background_color;
    }

    void set_viewplane(const ViewPlane& vp) {
        this->vp = vp;
    }

    const ViewPlane& get_viewplane() const {
        return vp;
    }

    const TracerPtr get_tracer() const {
        return tracer;
    }

    void set_sphere( const Sphere& sphere ) {
        this->sphere = sphere;
    }
    const Sphere& get_sphere() const {
        return sphere;
    }

private:
    RendererPtr                 renderer;
    TracerPtr                   tracer;

    ViewPlane					vp;
    RGBColor					background_color;

    Light*   					ambient_ptr;
    Camera*						camera_ptr;
    Sphere 						sphere;		// for Chapter 3 only
    Objects	                    objects;
    vector<Light*> 				lights;

    void delete_objects(void);
    void delete_lights(void);
};


inline void World::add_object(GeometricObject* object_ptr) {
    objects.push_back(object_ptr);
}


inline void World::add_light(Light* light_ptr) {
    lights.push_back(light_ptr);
}


inline void World::set_ambient_light(Light* light_ptr) {
    ambient_ptr = light_ptr;
}


inline void World::set_camera(Camera* c_ptr) {
    camera_ptr = c_ptr;
}


inline void World::set_renderer(RendererPtr renderer) {
    this->renderer = renderer;
}

inline void World::set_tracer(TracerPtr tracer) {
    this->tracer = tracer;
}

#endif
