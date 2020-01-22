#include <iostream>
#include <cmath>
#include "player_gun.h"
#include "irrlicht/irrlicht_handler.h"
#include "animated_mesh.h"
#include "map_mesh.h"
#include "vec3.h"

#define PI std::acos(-1)

int main()
{
    bool b_vsync = false;

    IrrlichtHandler irrlicht_handler(b_vsync);
    irrlicht_handler.create_device();

    AnimatedMesh *sydney = irrlicht_handler.add_animated_mesh("../irrlicht_engine/media/sydney.md2");
    irrlicht_handler.set_animated_mesh_texture(sydney, "../irrlicht_engine/media/sydney.bmp");

    irrlicht_handler.add_fps_camera(0,30,-40);

    AnimatedMesh *gun_mesh = irrlicht_handler.add_animated_mesh("resources/temp_gun/temp_gun.obj");
    irrlicht_handler.set_animated_mesh_parent_to_fps_camera(gun_mesh);

    vec3 gun_mesh_default_pos(3,-3,12);
    vec3 gun_mesh_default_rot(0,-120,0);
    vec3 gun_mesh_aimed_pos(0,-1,8);
    vec3 gun_mesh_aimed_rot(-60,-90,60);

    irrlicht_handler.set_animated_mesh_position(gun_mesh, gun_mesh_default_pos);
    irrlicht_handler.set_animated_mesh_rotation(gun_mesh, gun_mesh_default_rot);

    //Quake3 Level
    irrlicht_handler.load_file_archive("../irrlicht_engine/media/map-20kdm2.pk3");
    MapMesh* map = irrlicht_handler.add_octree_mesh("20kdm2.bsp");
    irrlicht_handler.set_map_mesh_position(map, vec3(-1300,-144,-1249));

    PlayerGun player_gun;

    unsigned int then = irrlicht_handler.get_time();
    const int move_speed = 3;
    while(irrlicht_handler.run())
    {
        unsigned int now = irrlicht_handler.get_time();
        const float frame_delta_time = (now-then)/1000.f;
        then = now;

        //User Input
        if(irrlicht_handler.is_key_down(irr::KEY_ESCAPE))
        {
            irrlicht_handler.close_device();
            break;
        }
        if(irrlicht_handler.is_key_down(irr::KEY_KEY_W))
        {
            const float rotY = irrlicht_handler.get_fps_camera_rotation_y();
            float dx = move_speed * std::sin(rotY*PI/180.f);
            float dz = move_speed * std::cos(rotY*PI/180.f);
            irrlicht_handler.move_fps_camera(dx, 0, dz);
        }
        if(irrlicht_handler.is_key_down(irr::KEY_KEY_S))
        {
            const float rotY = irrlicht_handler.get_fps_camera_rotation_y();
            float dx = move_speed * std::sin(rotY*PI/180.f);
            float dz = move_speed * std::cos(rotY*PI/180.f);
            irrlicht_handler.move_fps_camera(-dx, 0, -dz);
        }
        if(irrlicht_handler.is_key_down(irr::KEY_KEY_D))
        {
            const float rotY = irrlicht_handler.get_fps_camera_rotation_y();
            float dx = move_speed * std::sin((rotY+90)*PI/180.f);
            float dz = move_speed * std::cos((rotY+90)*PI/180.f);
            irrlicht_handler.move_fps_camera(dx, 0, dz);
        }
        if(irrlicht_handler.is_key_down(irr::KEY_KEY_A))
        {
            const float rotY = irrlicht_handler.get_fps_camera_rotation_y();
            float dx = move_speed * std::sin((rotY+90)*PI/180.f);
            float dz = move_speed * std::cos((rotY+90)*PI/180.f);
            irrlicht_handler.move_fps_camera(-dx, 0, -dz);
        }

        if(irrlicht_handler.is_mouse_down(1))
        {
            player_gun.try_aim_change();
        }

        player_gun.update(frame_delta_time);

        vec3 gun_mesh_position = irrlicht_handler.get_animated_mesh_position(gun_mesh);
        if(player_gun.get_aimed() && gun_mesh_position != gun_mesh_aimed_pos)
        {
            irrlicht_handler.set_animated_mesh_position(gun_mesh, gun_mesh_aimed_pos);
            irrlicht_handler.set_animated_mesh_rotation(gun_mesh, gun_mesh_aimed_rot);
        }
        else if(!player_gun.get_aimed() && gun_mesh_position == gun_mesh_aimed_pos)
        {
            irrlicht_handler.set_animated_mesh_position(gun_mesh, gun_mesh_default_pos);
            irrlicht_handler.set_animated_mesh_rotation(gun_mesh, gun_mesh_default_rot);
        }

        //Drawing
        irrlicht_handler.begin_drawing();
        irrlicht_handler.draw_scene();
        irrlicht_handler.draw_gui();
        irrlicht_handler.end_drawing();
    }

    irrlicht_handler.drop_device();

    return 0;
}
