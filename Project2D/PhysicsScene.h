#pragma once
#include <glm/glm.hpp>
#include <vector>

#include "Rigidbody.h"

class PhysicsObject;

#define SHAPE_COUNT 3

class PhysicsScene
{
public:
	PhysicsScene();
	~PhysicsScene();

	void addActor(PhysicsObject* actor);
	void removeActor(PhysicsObject* actor);
	void update(float dt);
	void draw();

	void setGravity(const glm::vec2 gravity);
	glm::vec2 getGravity() const;

	void setTimeStep(const float timeStep);
	float getTimeStep() const;

	static bool plane2Plane(PhysicsObject*, PhysicsObject*);
	static bool plane2Sphere(PhysicsObject*, PhysicsObject*);
	static bool plane2Box(PhysicsObject*, PhysicsObject*);
	static bool sphere2Plane(PhysicsObject*, PhysicsObject*);
	static bool sphere2Sphere(PhysicsObject*, PhysicsObject*);
	static bool sphere2Box(PhysicsObject*, PhysicsObject*);
	static bool box2Plane(PhysicsObject*, PhysicsObject*);
	static bool box2Sphere(PhysicsObject*, PhysicsObject*);
	static bool box2Box(PhysicsObject*, PhysicsObject*);

	static void  ApplyContactForces(Rigidbody* body1, Rigidbody* body2, glm::vec2 norm, float pen);

protected:
	glm::vec2 m_gravity;
	float m_timeStep;
	std::vector<PhysicsObject*> m_actors;
};

