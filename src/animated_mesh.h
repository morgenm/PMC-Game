#ifndef ANIMATED_MESH_H
#define ANIMATED_MESH_H

#include <irrlicht.h>

struct AnimatedMesh
{
    irr::scene::IAnimatedMesh *mesh;
    irr::scene::IAnimatedMeshSceneNode *node;
};

#endif
