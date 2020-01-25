#include "graphics_engine.h"

#include <iostream>

GraphicsEngine::GraphicsEngine(IrrlichtHandler *irr)
{
    irrlicht_handler = irr;
}

unsigned int GraphicsEngine::load_animated_mesh(std::string mesh_loc)
{
    IrrlichtMesh mesh = irrlicht_handler->add_animated_mesh(mesh_loc);

    unsigned int id = 0;
    while(animated_meshes.count(id) != 0)
    {
        id++;
    }

    animated_meshes[id] = mesh;
    return id;
}

void GraphicsEngine::add_fps_camera(vec3f pos)
{
    irrlicht_handler->add_fps_camera(pos);
}

void GraphicsEngine::set_animated_mesh_texture(unsigned int mesh_id, std::string texture_loc)
{
    irrlicht_handler->set_animated_mesh_texture(&animated_meshes[mesh_id], texture_loc);
}

void GraphicsEngine::set_animated_mesh_parent_to_fps_camera(unsigned int mesh_id)
{
    irrlicht_handler->set_animated_mesh_parent_to_fps_camera(&animated_meshes[mesh_id]);
}

void GraphicsEngine::set_animated_mesh_position(unsigned int mesh_id, vec3f pos)
{
    irrlicht_handler->set_animated_mesh_position(&animated_meshes[mesh_id], pos);
}

void GraphicsEngine::set_animated_mesh_rotation(unsigned int mesh_id, vec3f rot)
{
    irrlicht_handler->set_animated_mesh_rotation(&animated_meshes[mesh_id], rot);
}

void GraphicsEngine::load_map_mesh_from_file(std::string map_loc, std::string map_name)
{
    irrlicht_handler->load_file_archive(map_loc);
    loaded_map = irrlicht_handler->add_octree_mesh(map_name);
}

void GraphicsEngine::set_map_mesh_position(vec3f pos)
{
    irrlicht_handler->set_map_mesh_position(&loaded_map, pos);
}
