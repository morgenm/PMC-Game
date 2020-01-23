#ifndef ANIMATED_MESH_H
#define ANIMATED_MESH_H

#include <irrlicht.h>

struct IrrlichtMesh
{
    irr::scene::IAnimatedMesh *mesh;
    irr::scene::IAnimatedMeshSceneNode *node;
};

#endif
