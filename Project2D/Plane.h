#pragma once
#include "PhysicsObject.h"


class Rigidbody;

class Plane : public PhysicsObject
{
public:
	Plane();
	Plane(glm::vec2 normal, float distance, float elasticity);
	~Plane();

	virtual void fixedUpdate(glm::vec2 gravity, float timeStep) {};
	virtual void draw();
	virtual void resetPosition();

	glm::vec2 getNormal();
	float getDistance();

	void resolveCollision(Rigidbody* other, glm::vec2 contact);
	float GetElasticity() const;

protected:
	glm::vec2 m_normal;
	float m_distanceToOrigin;
	glm::vec4 m_colour;
};

