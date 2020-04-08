#include <iostream>
#include <cmath>
#include <memory>

#include "player.h"
#include "player_gun.h"
#include "irrlicht/irrlicht_handler.h"
#include "graphics_engine.h"
#include "vec3.h"
#include "box.h"
#include "physics_engine.h"

#define PI std::acos(-1)

int main()
{
    bool b_vsync = true;
    bool b_fullscreen = true;
    unsigned int i_width = 1920;
    unsigned int i_height = 1080;

    IrrlichtHandler irrlicht_handler(b_vsync, b_fullscreen,
        i_width, i_height);
    irrlicht_handler.create_device();

    GraphicsEngine graphics_engine(&irrlicht_handler);
    PhysicsEngine physics_engine;

    unsigned int sydney = graphics_engine.load_animated_mesh("../../irrlicht_engine/media/sydney.md2");
    graphics_engine.set_animated_mesh_texture(sydney, "../../irrlicht_engine/media/sydney.bmp");
    graphics_engine.set_animated_mesh_position(sydney, vec3f(1,0,1));

    float sydney_scalar = 1/graphics_engine.get_animated_mesh_height(sydney);
    graphics_engine.set_animated_mesh_scale(sydney, vec3f(sydney_scalar,sydney_scalar,sydney_scalar));

    std::cout << "Sydney loaded\n";

    graphics_engine.add_fps_camera(vec3f(0,0,0));

    unsigned int gun_mesh = graphics_engine.load_animated_mesh("../resources/temp_gun/temp_gun.obj");
    graphics_engine.set_animated_mesh_parent_to_fps_camera(gun_mesh);

    std::cout << "Gun loaded\n";

    vec3f gun_mesh_default_pos(0.05,-0.05,0.05);
    vec3f gun_mesh_default_rot(0,-120,0);
    vec3f gun_mesh_aimed_pos(0,-1,8);
    vec3f gun_mesh_aimed_rot(-60,-90,60);

    float gun_scalar = (0.01)*graphics_engine.get_animated_mesh_height(gun_mesh);
    graphics_engine.set_animated_mesh_scale(gun_mesh, vec3f(gun_scalar, gun_scalar, gun_scalar));
    graphics_engine.set_animated_mesh_position(gun_mesh, gun_mesh_default_pos);
    graphics_engine.set_animated_mesh_rotation(gun_mesh, gun_mesh_default_rot);

    //Quake3 Level
    graphics_engine.load_map_mesh_from_file("../../irrlicht_engine/media/map-20kdm2.pk3", "20kdm2.bsp");
    graphics_engine.set_map_mesh_position(vec3f(-20,-2,-20));
    float map_scalar = 10/graphics_engine.get_map_mesh_height();
    graphics_engine.set_map_mesh_scale(vec3f(map_scalar,map_scalar,map_scalar));
    std::cout << "Map loaded\n";

    Box box(vec3f(1,0,2), vec3f(0,0,0));
    unsigned int box_mesh = graphics_engine.load_animated_mesh("../resources/temp_box/temp_box.obj");
    graphics_engine.set_animated_mesh_texture(box_mesh, "../resources/temp_box/temp_box.jpg");
    graphics_engine.set_animated_mesh_position(box_mesh, box.get_position());
    graphics_engine.set_animated_mesh_rotation(box_mesh, box.get_rotation());

    float box_scalar = 1/graphics_engine.get_animated_mesh_height(box_mesh);
    graphics_engine.set_animated_mesh_scale(box_mesh, vec3f(box_scalar,box_scalar,box_scalar));

    std::cout << "Box loaded\n";

    Player player(vec3f(0,0,0));
    PlayerGun player_gun;
    bool player_walk = false;

    unsigned int ground_rig_body = physics_engine.create_rigid_body(
        PhysicsShape::BoxShape, vec3f(50,1,50), vec3f(0,-2.5,0), 0
    );
    unsigned int box_rig_body = physics_engine.create_rigid_body(
        PhysicsShape::BoxShape, vec3f(1,1,1), box.get_position(), 100
    );

    unsigned int then = irrlicht_handler.get_time();

    while(irrlicht_handler.run())
    {
        const unsigned int now = irrlicht_handler.get_time();
        const float frame_delta_time = (now-then)/1000.f;

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

        //dynamics_world->stepSimulation(frame_delta_time);
        physics_engine.step_simulation(frame_delta_time);
        then = now;
        box.set_position(physics_engine.get_rigid_body_pos(box_rig_body));
        std::cout << physics_engine.get_rigid_body_pos(box_rig_body).y << '\n';

        graphics_engine.set_animated_mesh_position(box_mesh, box.get_position());
        graphics_engine.set_animated_mesh_rotation(box_mesh, box.get_rotation());

        //Drawing
        irrlicht_handler.begin_drawing();
        irrlicht_handler.draw_scene();
        irrlicht_handler.draw_gui();
        irrlicht_handler.end_drawing();

    }

    irrlicht_handler.drop_device();

    /*for(int i=dynamics_world->getNumCollisionObjects()-1; i>=0; i--)
    {
        btCollisionObject *obj = dynamics_world->getCollisionObjectArray()[i];
        btRigidBody *rb = btRigidBody::upcast(obj);
        if(rb && rb->getMotionState())
        {
            delete rb->getMotionState();
        }
        dynamics_world->removeCollisionObject(obj);
        delete obj;
    }*/

    return 0;
}
