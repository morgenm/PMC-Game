#ifndef GRAPHICS_ENGINE_H
#define GRAPHICS_ENGINE_H

#include <string>
#include <map>

#include "irrlicht/irrlicht_handler.h"
#include "irrlicht/irrlicht_mesh.h"
#include "irrlicht/map_mesh.h"
#include "vec3.h"

class GraphicsEngine
{
    struct Line
    {
        vec3f start, end;
        Line(const vec3f &s, const vec3f &e)
        :start(s), end(e)
        {}
    };

    IrrlichtHandler *irrlicht_handler;

    //Each irrlicht mesh is represented by an int.
    std::map<unsigned int, IrrlichtMesh> animated_meshes; //TO FIX: Graphics engine should not own the meshes, only pointers.

    //Lines used to draw physics meshes
    std::vector<Line> lines;

    MapMesh loaded_map;

public:
    GraphicsEngine(IrrlichtHandler *irr);

    void add_fps_camera(vec3f pos);

    //Animated Meshes
    unsigned int load_animated_mesh(std::string mesh_loc);
    void set_animated_mesh_texture(unsigned int mesh_id, std::string texture_loc);
    void set_animated_mesh_parent_to_fps_camera(unsigned int mesh_id);
    void set_animated_mesh_position(unsigned int mesh_id, vec3f pos);
    void set_animated_mesh_rotation(unsigned int mesh_id, vec3f rot);
    void set_animated_mesh_scale(unsigned int mesh_id, vec3f scale);

    float get_animated_mesh_height(unsigned int mesh_id);

    //Draw a line
    void draw_line(const vec3f &start, const vec3f &end);

    void load_map_mesh_from_file(std::string map_loc, std::string map_name);
    void set_map_mesh_position(vec3f pos);
    void set_map_mesh_scale(vec3f scale);

    float get_map_mesh_height();

    //Move those irrlicht calls from main to here in draw. Should be called
    //every frame.
    void draw();
};

#endif
