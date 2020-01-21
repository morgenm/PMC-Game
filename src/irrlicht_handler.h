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
#include "animated_mesh.h"
#include "vec3.h"

class IrrlichtHandler
{
    PMCEventReceiver pmc_event_receiver;
    irr::IrrlichtDevice *irr_device;
    const bool b_vsync;

    irr::video::IVideoDriver *driver;
    irr::scene::ISceneManager *scene_mgr;
    irr::gui::IGUIEnvironment *gui_env;

    irr::scene::ICameraSceneNode *fps_camera;

    std::vector<AnimatedMesh> animated_meshes; //Move this to graphics engine
public:
    IrrlichtHandler(bool vsync);

    bool create_device(); //Create an irrlicht device
    void drop_device();
    void close_device();
    bool run();

    void begin_drawing();
    void end_drawing();
    void draw_scene();
    void draw_gui();

    AnimatedMesh* add_animated_mesh(std::string mesh_loc);
    void set_animated_mesh_texture(AnimatedMesh* mesh, std::string texture_loc);
    void set_animated_mesh_parent_to_fps_camera(AnimatedMesh *mesh);

    void set_animated_mesh_position(AnimatedMesh *mesh, float x, float y, float z);
    void set_animated_mesh_position(AnimatedMesh *mesh, vec3 pos);
    void set_animated_mesh_rotation(AnimatedMesh *mesh, vec3 rot);

    vec3 get_animated_mesh_position(AnimatedMesh *mesh) const;
    vec3 get_animed_mesh_rotation(AnimatedMesh *mesh) const;

    void add_fps_camera(int x, int y, int z);
    void move_fps_camera(float dx, float dy, float dz);
    float get_fps_camera_rotation_x() const;
    float get_fps_camera_rotation_y() const;
    float get_fps_camera_rotation_z() const;

    bool is_key_down(irr::EKEY_CODE key) const;
    bool is_mouse_down(int mouse_button) const;

    unsigned int get_time() const;
};

#endif
