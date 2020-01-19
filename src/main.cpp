#include <iostream>
#include <irrlicht.h>
#include <cmath>

class PMCEventReceiver : public irr::IEventReceiver //Custom irrlicht event receiver
{
    bool KeyIsDown[irr::KEY_KEY_CODES_COUNT]; //Stores the current state (up/down) of each key
    bool MouseIsDown[3];

public:
    virtual bool OnEvent(const irr::SEvent& event)
    {
        if(event.EventType == irr::EET_KEY_INPUT_EVENT)
            KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown; //Store if the key is down or not

        else if(event.EventType == irr::EET_MOUSE_INPUT_EVENT)
        {
            MouseIsDown[0] = event.MouseInput.isLeftPressed();
            MouseIsDown[1] = event.MouseInput.isRightPressed();
            MouseIsDown[2] = event.MouseInput.isMiddlePressed();
        }
        return false; //I don't know why this is here???
    }

    virtual bool IsKeyDown(irr::EKEY_CODE keyCode) const //Check if key is pressed
    {
        return KeyIsDown[keyCode];
    }

    bool IsMouseDown(int i) const
    {
        return MouseIsDown[i];
    }

    PMCEventReceiver()
    {
        for(irr::u32 i=0; i<irr::KEY_KEY_CODES_COUNT; i++)
            KeyIsDown[i] = false;
    }
};

int main()
{
    bool vsync = false;

    PMCEventReceiver p_event_receiver;

    irr::IrrlichtDevice *irr_device = irr::createDevice(irr::video::EDT_OPENGL,
        irr::core::dimension2d<irr::u32>(640,480), 16, false, false, vsync, &p_event_receiver);
    if(!irr_device)
        return 1;

    irr_device->setWindowCaption(L"PMC Game");

    irr::video::IVideoDriver *driver = irr_device->getVideoDriver();
    irr::scene::ISceneManager *scene_mgr = irr_device->getSceneManager();
    irr::gui::IGUIEnvironment *gui_env = irr_device->getGUIEnvironment();

    gui_env->addStaticText(L"PMC Game 1.0", irr::core::rect<irr::s32>(10,10,260,22), false);


    //Mesh for temp built-in character
    irr::scene::IAnimatedMesh *mesh = scene_mgr->getMesh("../irrlicht_engine/media/sydney.md2");
    if(!mesh)
    {
        irr_device->drop();
        return 0;
    }

    //Node for the temp character
    irr::scene::IAnimatedMeshSceneNode *node = scene_mgr->addAnimatedMeshSceneNode(mesh);
    if(node)
    {
        node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
        node->setMD2Animation(irr::scene::EMAT_STAND);
        node->setMaterialTexture(0, driver->getTexture("../irrlicht_engine/media/sydney.bmp"));
    }

    //FPS Camera
    irr::scene::ICameraSceneNode *fps_camera = scene_mgr->addCameraSceneNodeFPS();
    fps_camera->setPosition(irr::core::vector3df(0,30,-40));
    irr_device->getCursorControl()->setVisible(false);

    irr::scene::IAnimatedMesh *gun_mesh = scene_mgr->getMesh("resources/temp_gun/temp_gun.obj");
    if(!gun_mesh)
    {
        irr_device->drop();
        return 0;
    }

    irr::scene::IAnimatedMeshSceneNode *gun_node = scene_mgr->addAnimatedMeshSceneNode(gun_mesh, fps_camera);
    if(gun_node)
    {
        gun_node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
        gun_node->setPosition(irr::core::vector3df(3,-3,12));
        gun_node->setRotation(irr::core::vector3df(0,-120,0));
    }

    //Used to get delta time between frames
    int lastFPS = -1;
    irr::u32 then = irr_device->getTimer()->getTime();

    bool gun_aimed = false;
    irr::f32 time_since_aim_switch = 0;
    irr::f32 aim_time_wait = 0.2;
    while(irr_device->run())
    {
        //Frame delta time
        const irr::u32 now = irr_device->getTimer()->getTime();
        const irr::f32 frame_delta_time = (irr::f32) (now-then)/1000.f;
        then = now;

        time_since_aim_switch += frame_delta_time;

        if(p_event_receiver.IsKeyDown(irr::KEY_ESCAPE)) //Escape key pressed
        {
            irr_device->closeDevice(); //Close the window
            break;
        }
        //Camera movement
        const irr::core::vector3df fps_camera_position = fps_camera->getPosition();
        const irr::core::vector3df rot = fps_camera->getRotation();
        const double pi = std::acos(-1); //arccos of -1 is pi
        const int move_speed = 3;
        if(p_event_receiver.IsKeyDown(irr::KEY_KEY_W))
        {
            float x = move_speed  * std::sin(rot.Y*pi/180.f);
            float z = move_speed  * std::cos(rot.Y*pi/180.f);
            const irr::core::vector3df new_pos(fps_camera_position.X+x, fps_camera_position.Y, fps_camera_position.Z+z);
            fps_camera->setPosition(new_pos);
        }
        if(p_event_receiver.IsKeyDown(irr::KEY_KEY_S))
        {
            float x = move_speed  * std::sin(rot.Y*pi/180.f);
            float z = move_speed  * std::cos(rot.Y*pi/180.f);
            const irr::core::vector3df new_pos(fps_camera_position.X-x, fps_camera_position.Y, fps_camera_position.Z-z);
            fps_camera->setPosition(new_pos);
        }
        if(p_event_receiver.IsKeyDown(irr::KEY_KEY_D))
        {
            float x = move_speed  * std::sin((rot.Y+90)*pi/180.f);
            float z = move_speed  * std::cos((rot.Y+90)*pi/180.f);
            const irr::core::vector3df new_pos(fps_camera_position.X+x, fps_camera_position.Y, fps_camera_position.Z+z);
            fps_camera->setPosition(new_pos);
        }
        if(p_event_receiver.IsKeyDown(irr::KEY_KEY_A))
        {
            float x = move_speed  * std::sin((rot.Y+90)*pi/180.f);
            float z = move_speed  * std::cos((rot.Y+90)*pi/180.f);
            const irr::core::vector3df new_pos(fps_camera_position.X-x, fps_camera_position.Y, fps_camera_position.Z-z);
            fps_camera->setPosition(new_pos);
        }

        if(p_event_receiver.IsMouseDown(1))
        {
            if(!gun_aimed && time_since_aim_switch > aim_time_wait) //Aim the gun
            {
                gun_aimed = true;
                time_since_aim_switch = 0;
                gun_node->setPosition(irr::core::vector3df(0,-1,8));
                gun_node->setRotation(irr::core::vector3df(-60,-90,60));
            }
            else if(gun_aimed && time_since_aim_switch > aim_time_wait)
            {
                gun_aimed = false;
                time_since_aim_switch = 0;
                gun_node->setPosition(irr::core::vector3df(3,-3,12));
                gun_node->setRotation(irr::core::vector3df(0,-120,0));
            }
        }

        driver->beginScene(true, true, irr::video::SColor(255,0,100,255));
        scene_mgr->drawAll();
        gui_env->drawAll();
        driver->endScene();
    }

    irr_device->drop();

    return 0;
}
