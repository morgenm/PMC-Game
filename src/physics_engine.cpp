#include <iostream>
#include "physics_engine.h"

PhysicsEngine::PhysicsEngine()
{
	col_config = std::make_unique<btDefaultCollisionConfiguration>();
    dispatcher = std::make_unique<btCollisionDispatcher>(col_config.get());
    overlapping_pair_cache = std::make_unique<btDbvtBroadphase>();
    solver = std::make_unique<btSequentialImpulseConstraintSolver>();
    dynamics_world = std::make_unique<btDiscreteDynamicsWorld>(
        dispatcher.get(), overlapping_pair_cache.get(), solver.get(), col_config.get()
    );
	dynamics_world->setGravity(btVector3(0,-10,0));
	std::cout << "Physics Setup complete.\n";
}

PhysicsEngine::~PhysicsEngine()
{
	for(auto it=col_shapes.begin(); it!=col_shapes.end(); it++)
	{
		delete *it;
	}
	for(auto it=rigid_bodies.begin(); it!=rigid_bodies.end(); it++)
	{
		dynamics_world.get()->removeRigidBody(it->second);
		delete it->second;
	}
}

void PhysicsEngine::step_simulation(const float frame_delta_time)
{
	dynamics_world->stepSimulation(frame_delta_time);
}

unsigned int PhysicsEngine::create_rigid_body(PhysicsShape shape, vec3f shape_dimensions, vec3f pos, float mass)
{
	btCollisionShape *col_shape = NULL;
	switch(shape)
	{
		case PhysicsShape::BoxShape:
		{
			col_shape = new btBoxShape(btVector3(shape_dimensions.x, shape_dimensions.y, shape_dimensions.z));
		}
	}

	col_shapes.insert(col_shape);

	btTransform transform;
	transform.setIdentity();
	transform.setOrigin(btVector3(
			pos.x,
			pos.y,
			pos.z
	));

	btDefaultMotionState *m_state = new btDefaultMotionState(transform);
	btRigidBody::btRigidBodyConstructionInfo c_info(mass, m_state, col_shape, btVector3(0,0,0));
	btRigidBody *rig = new btRigidBody(c_info);

	dynamics_world->addRigidBody(rig);

	unsigned int uid = 0;
	while(rigid_bodies.count(uid) != 0)
		uid++;

	rigid_bodies[uid] = rig;
	return uid;
}

vec3f PhysicsEngine::get_rigid_body_pos(unsigned int rig) const
{
	btTransform rig_transform;
	rigid_bodies.at(rig)->getMotionState()->getWorldTransform(rig_transform);

	return vec3f(
		rig_transform.getOrigin().getX(), rig_transform.getOrigin().getY(),
		rig_transform.getOrigin().getZ()
	);
}
