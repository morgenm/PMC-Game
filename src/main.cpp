#include <iostream>
#include <cmath>
#include "player.h"
#include "player_gun.h"
#include "irrlicht/irrlicht_handler.h"
#include "graphics_engine.h"
#include "vec3.h"

#define PI std::acos(-1)

int main()
{
    bool b_vsync = false;
    bool b_fullscreen = false;
    unsigned int i_width = 1280;
    unsigned int i_height = 720;

    IrrlichtHandler irrlicht_handler(b_vsync, b_fullscreen,
        i_width, i_height);
    irrlicht_handler.create_device();

    GraphicsEngine graphics_engine(&irrlicht_handler);

    unsigned int sydney = graphics_engine.load_animated_mesh("../irrlicht_engine/media/sydney.md2");
    graphics_engine.set_animated_mesh_texture(sydney, "../irrlicht_engine/media/sydney.bmp");

    graphics_engine.add_fps_camera(vec3f(0,30,-40));

    unsigned int gun_mesh = graphics_engine.load_animated_mesh("resources/temp_gun/temp_gun.obj");
    graphics_engine.set_animated_mesh_parent_to_fps_camera(gun_mesh);

    vec3f gun_mesh_default_pos(3,-3,12);
    vec3f gun_mesh_default_rot(0,-120,0);
    vec3f gun_mesh_aimed_pos(0,-1,8);
    vec3f gun_mesh_aimed_rot(-60,-90,60);

    graphics_engine.set_animated_mesh_position(gun_mesh, gun_mesh_default_pos);
    graphics_engine.set_animated_mesh_rotation(gun_mesh, gun_mesh_default_rot);

    //Quake3 Level
    graphics_engine.load_map_mesh_from_file("../irrlicht_engine/media/map-20kdm2.pk3", "20kdm2.bsp");
    graphics_engine.set_map_mesh_position(vec3f(-1300,-144,-1249));

    Player player(vec3f(0,0,0));
    PlayerGun player_gun;
    bool player_walk = false;

    unsigned int then = irrlicht_handler.get_time();

    while(irrlicht_handler.run())
    {
        unsigned int now = irrlicht_handler.get_time();
        const float frame_delta_time = (now-then)/1000.f;
        then = now;

        vec3f player_move_vec(0,0,0);

        //User Input
        if(irrlicht_handler.is_key_down(irr::KEY_ESCAPE))
        {
            irrlicht_handler.close_device();
            break;
        }
        if(irrlicht_handler.is_key_down(irr::KEY_KEY_W))
        {
            const float rotY = irrlicht_handler.get_fps_camera_rotation_y();
            float dx = std::sin(rotY*PI/180.f);
            float dz = std::cos(rotY*PI/180.f);
            if(!isnan(dx))
                player_move_vec.x += dx;
            if(!isnan(dz))
                player_move_vec.z += dz;
            player_walk = true;
        }
        if(irrlicht_handler.is_key_down(irr::KEY_KEY_S))
        {
            const float rotY = irrlicht_handler.get_fps_camera_rotation_y();
            float dx = std::sin(rotY*PI/180.f);
            float dz = std::cos(rotY*PI/180.f);
            if(!isnan(dx))
                player_move_vec.x -= dx;
            if(!isnan(dz))
                player_move_vec.z -= dz;
            player_walk = true;
        }
        if(irrlicht_handler.is_key_down(irr::KEY_KEY_D))
        {
            const float rotY = irrlicht_handler.get_fps_camera_rotation_y();
            float dx = std::sin((rotY+90)*PI/180.f);
            float dz =  std::cos((rotY+90)*PI/180.f);
            if(!isnan(dx))
                player_move_vec.x += dx;
            if(!isnan(dz))
                player_move_vec.z += dz;
            player_walk = true;
        }
        if(irrlicht_handler.is_key_down(irr::KEY_KEY_A))
        {
            const float rotY = irrlicht_handler.get_fps_camera_rotation_y();
            float dx = std::sin((rotY+90)*PI/180.f);
            float dz = std::cos((rotY+90)*PI/180.f);
            if(!isnan(dx))
                player_move_vec.x -= dx;
            if(!isnan(dz))
                player_move_vec.z -= dz;
            player_walk = true;
        }

        if(irrlicht_handler.is_mouse_down(1))
        {
            player_gun.try_aim_change();
        }


        irrlicht_handler.set_fps_camera_position(player.get_position());

        if(player_move_vec.get_magnitude() != 0)
            player.walk(player_move_vec.get_normalized());
        else
            player_walk = false;
        player_move_vec = vec3f(0,0,0);

        if(!player_walk)
            player.stop_walk();
        else
            player_walk = false;

        player.update();
        player_gun.update(frame_delta_time);


        /*vec3 gun_mesh_position = irrlicht_handler.get_animated_mesh_position(gun_mesh);
        if(player_gun.get_aimed() && gun_mesh_position != gun_mesh_aimed_pos)
        {
            irrlicht_handler.set_animated_mesh_position(gun_mesh, gun_mesh_aimed_pos);
            irrlicht_handler.set_animated_mesh_rotation(gun_mesh, gun_mesh_aimed_rot);
        }
        else if(!player_gun.get_aimed() && gun_mesh_position == gun_mesh_aimed_pos)
        {
            irrlicht_handler.set_animated_mesh_position(gun_mesh, gun_mesh_default_pos);
            irrlicht_handler.set_animated_mesh_rotation(gun_mesh, gun_mesh_default_rot);
        }*/

        //Drawing
        irrlicht_handler.begin_drawing();
        irrlicht_handler.draw_scene();
        irrlicht_handler.draw_gui();
        irrlicht_handler.end_drawing();
    }

    irrlicht_handler.drop_device();

    return 0;
}
