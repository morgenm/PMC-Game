#include "irrlicht_handler.h"
#include <string>

IrrlichtHandler::IrrlichtHandler(bool vsync)
:b_vsync(vsync)
{

}

bool IrrlichtHandler::create_device()
{
    irr_device = irr::createDevice(irr::video::EDT_OPENGL,
        irr::core::dimension2d<irr::u32>(640,480), 16, false, false, b_vsync, &pmc_event_receiver);
    if(!irr_device)
        return false;

    irr_device->setWindowCaption(L"PMC Game Alpha");

    driver = irr_device->getVideoDriver();
    scene_mgr = irr_device->getSceneManager();
    gui_env = irr_device->getGUIEnvironment();

    gui_env->addStaticText(L"PMC Game 1.0", irr::core::rect<irr::s32>(10,10,260,22), false);
    return true;
}

void IrrlichtHandler::drop_device()
{
    irr_device->drop();
    return;
}

void IrrlichtHandler::close_device()
{
    irr_device->closeDevice();
    return;
}

bool IrrlichtHandler::run()
{
    return irr_device->run();
}

void IrrlichtHandler::begin_drawing()
{
    driver->beginScene(true, true, irr::video::SColor(255,0,100,255));
}

void IrrlichtHandler::end_drawing()
{
    driver->endScene();
}

void IrrlichtHandler::draw_scene()
{
    scene_mgr->drawAll();
}

void IrrlichtHandler::draw_gui()
{
    gui_env->drawAll();
}

IrrlichtMesh IrrlichtHandler::add_animated_mesh(std::string mesh_loc)
{
    IrrlichtMesh new_mesh;
    new_mesh.mesh = scene_mgr->getMesh(mesh_loc.c_str());

    new_mesh.node = scene_mgr->addAnimatedMeshSceneNode(new_mesh.mesh);

    new_mesh.node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    return new_mesh;
    //animated_meshes.push_back(new_mesh);
    //return &animated_meshes.back();
    //node->setMD2Animation(irr::scene::EMAT_STAND);
}

void IrrlichtHandler::set_animated_mesh_texture(IrrlichtMesh* mesh, std::string texture_loc)
{
    mesh->node->setMaterialTexture(0, driver->getTexture(texture_loc.c_str()));
    return;
}

void IrrlichtHandler::set_animated_mesh_parent_to_fps_camera(IrrlichtMesh *mesh)
{
    mesh->node->setParent(fps_camera);
}

void IrrlichtHandler::set_animated_mesh_position(IrrlichtMesh *mesh, float x, float y, float z)
{
    mesh->node->setPosition(irr::core::vector3df(x,y,z));
}

void IrrlichtHandler::set_animated_mesh_position(IrrlichtMesh *mesh, vec3 pos)
{
    mesh->node->setPosition(pos);
}

void IrrlichtHandler::set_animated_mesh_rotation(IrrlichtMesh *mesh, vec3 rot)
{
    mesh->node->setRotation(rot);
}

vec3 IrrlichtHandler::get_animated_mesh_position(IrrlichtMesh *mesh) const
{
    return mesh->node->getPosition();
}

vec3 IrrlichtHandler::get_animed_mesh_rotation(IrrlichtMesh *mesh) const
{
    return mesh->node->getRotation();
}

void IrrlichtHandler::add_fps_camera(vec3 pos)
{
    fps_camera = scene_mgr->addCameraSceneNodeFPS();
    fps_camera->setPosition(pos);
    irr_device->getCursorControl()->setVisible(false);
}

void IrrlichtHandler::move_fps_camera(float dx, float dy, float dz)
{
    const irr::core::vector3df fps_camera_position = fps_camera->getPosition();
    const irr::core::vector3df new_pos(fps_camera_position.X+dx,
        fps_camera_position.Y+dy, fps_camera_position.Z+dz);
    fps_camera->setPosition(new_pos);
}
float IrrlichtHandler::get_fps_camera_rotation_x() const
{
    return fps_camera->getRotation().X;
}

float IrrlichtHandler::get_fps_camera_rotation_y() const
{
    return fps_camera->getRotation().Y;
}

float IrrlichtHandler::get_fps_camera_rotation_z() const
{
    return fps_camera->getRotation().Z;
}

bool IrrlichtHandler::is_key_down(irr::EKEY_CODE key) const
{
    return pmc_event_receiver.IsKeyDown(key);
}

bool IrrlichtHandler::is_mouse_down(int mouse_button) const
{
    return pmc_event_receiver.IsMouseDown(mouse_button);
}

unsigned int IrrlichtHandler::get_time() const
{
    return irr_device->getTimer()->getTime();
}

void IrrlichtHandler::load_file_archive(std::string archive_loc)
{
    irr_device->getFileSystem()->addFileArchive(archive_loc.c_str());
}

MapMesh IrrlichtHandler::add_octree_mesh(std::string mesh_name)
{
    MapMesh new_mesh;
    new_mesh.mesh = scene_mgr->getMesh(mesh_name.c_str());

    new_mesh.node = scene_mgr->addOctreeSceneNode(new_mesh.mesh->getMesh(0),
        0, -1, 1024);

    return new_mesh;
}

void IrrlichtHandler::set_map_mesh_position(MapMesh* mesh, vec3 pos)
{
    mesh->node->setPosition(pos);
}
