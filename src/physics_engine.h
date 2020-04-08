#ifndef PHYSICS_ENGINE_H
#define PHYSICS_ENGINE_H

#include <memory>
#include <set>
#include <map>
#include "btBulletDynamicsCommon.h"
#include "vec3.h"

enum PhysicsShape
{
	BoxShape,
};

class PhysicsEngine
{
	std::unique_ptr<btDefaultCollisionConfiguration> col_config;
	std::unique_ptr<btCollisionDispatcher> dispatcher;
	std::unique_ptr<btBroadphaseInterface> overlapping_pair_cache;
	std::unique_ptr<btSequentialImpulseConstraintSolver> solver;
	std::unique_ptr<btDiscreteDynamicsWorld> dynamics_world;

	std::set<btCollisionShape*> col_shapes;
	std::map<unsigned int, btRigidBody*> rigid_bodies;

public:
	//void init();
	PhysicsEngine();
	~PhysicsEngine();

	void step_simulation(const float frame_delta_time);

	unsigned int create_rigid_body(PhysicsShape shape, vec3f shape_dimensions, vec3f pos, float mass);
	vec3f get_rigid_body_pos(unsigned int rig) const;
};

#endif
