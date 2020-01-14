#include <iostream>
#include <irrlicht.h>

int main()
{
    bool vsync = false;

    irr::IrrlichtDevice *irr_device = irr::createDevice(irr::video::EDT_OPENGL,
        irr::core::dimension2d<irr::u32>(640,480), 16, false, false, vsync, 0);
    if(!irr_device)
        return 1;

    irr_device->setWindowCaption(L"PMC Game");

    irr::video::IVideoDriver *driver = irr_device->getVideoDriver();
    irr::scene::ISceneManager *scene_mgr = irr_device->getSceneManager();
    irr::gui::IGUIEnvironment *gui_env = irr_device->getGUIEnvironment();

    gui_env->addStaticText(L"PMC Game 1.0", irr::core::rect<irr::s32>(10,10,260,22), false);


    irr::scene::IAnimatedMesh *mesh = scene_mgr->getMesh("../irrlicht_engine/media/sydney.md2");
    if(!mesh)
    {
        irr_device->drop();
        return 0;
    }

    irr::scene::IAnimatedMeshSceneNode *node = scene_mgr->addAnimatedMeshSceneNode(mesh);
    if(node)
    {
        node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
        node->setMD2Animation(irr::scene::EMAT_STAND);
        node->setMaterialTexture(0, driver->getTexture("../irrlicht_engine/media/sydney.bmp"));
    }

    scene_mgr->addCameraSceneNode(0, irr::core::vector3df(0,30,-40), irr::core::vector3df(0,5,0));

    while(irr_device->run())
    {
        driver->beginScene(true, true, irr::video::SColor(255,0,100,255));
        scene_mgr->drawAll();
        gui_env->drawAll();
        driver->endScene();
    }

    irr_device->drop();

    return 0;
}
