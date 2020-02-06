/*
irrlicht_handler.h
This contains the IrrlichtHandler class.
The purpose of this class is to abstract away irrlicht functionality so that
in theory, it should be easy to replace irrlicht with another library with
similar functionality.
*/

#ifndef IRRLICHT_HANDLER_H
#define IRRLICHT_HANDLER_H

#include <irrlicht.h>
#include <vector>
#include <string>
#include "pmc_event_receiver.h"
#include "irrlicht_mesh.h"
#include "../vec3.h"
#include "map_mesh.h"

class IrrlichtHandler
{
    PMCEventReceiver pmc_event_receiver;
    irr::IrrlichtDevice *irr_device;
    bool b_vsync;
    bool b_fullscreen;
    unsigned int i_width;
    unsigned int i_height;

    irr::video::IVideoDriver *driver;
    irr::scene::ISceneManager *scene_mgr;
    irr::gui::IGUIEnvironment *gui_env;

    irr::scene::ICameraSceneNode *fps_camera;

    irr::core::vector3df vec3f_to_vector3df(vec3f v) const;
    vec3f vector3df_to_vec3f(irr::core::vector3df v) const;

public:
    IrrlichtHandler(bool vsync, bool fullscreen,
        unsigned int width, unsigned int height);

    bool create_device(); //Create an irrlicht device
    void drop_device();
    void close_device();
    bool run();

    void begin_drawing();
    void end_drawing();
    void draw_scene();
    void draw_gui();

    IrrlichtMesh add_animated_mesh(std::string mesh_loc);
    void set_animated_mesh_texture(IrrlichtMesh *mesh, std::string texture_loc);
    void set_animated_mesh_parent_to_fps_camera(IrrlichtMesh *mesh);

    void set_animated_mesh_position(IrrlichtMesh *mesh, float x, float y, float z);
    void set_animated_mesh_position(IrrlichtMesh *mesh, vec3f pos);
    void set_animated_mesh_rotation(IrrlichtMesh *mesh, vec3f rot);
    void set_animated_mesh_scale(IrrlichtMesh *mesh, vec3f scale);

    vec3f get_animated_mesh_position(IrrlichtMesh *mesh) const;
    vec3f get_animed_mesh_rotation(IrrlichtMesh *mesh) const;

    void add_fps_camera(vec3f pos);
    void move_fps_camera(float dx, float dy, float dz);
    void set_fps_camera_position(vec3f pos);
    float get_fps_camera_rotation_x() const;
    float get_fps_camera_rotation_y() const;
    float get_fps_camera_rotation_z() const;

    bool is_key_down(irr::EKEY_CODE key) const;
    bool is_mouse_down(int mouse_button) const;

    unsigned int get_time() const;

    void load_file_archive(std::string archive_loc);

    /* Load an octree mesh. This is an optimized mesh handled by irrlicht which
    only loads visible geometry. */
    MapMesh add_octree_mesh(std::string mesh_name);
    void set_map_mesh_position(MapMesh* mesh, vec3f pos);
    void set_map_mesh_scale(MapMesh* mesh, vec3f scale);
};
#endif
