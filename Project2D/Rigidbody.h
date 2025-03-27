#pragma once
#include "PhysicsObject.h"
class Rigidbody : public PhysicsObject
{
public:
	Rigidbody(ShapeType shapeID, glm::vec2 position, glm::vec2 velocity, float orientation, float mass,
		float angularVelocity, float elasticity);
	~Rigidbody();

	virtual void fixedUpdate(glm::vec2 gravity, float timeStep);
	void applyForce(glm::vec2 force, glm::vec2 pos = glm::vec2(0, 0));
	//void applyForceToActor(Rigidbody* actor2, glm::vec2 force);

	glm::vec2 getPosition() const;
	float getOrientation() const;
	glm::vec2 getVelocity() const;
	float getMass() const;
	float getMoment() const;
	float getElasticity() const;
	float getAngularVelocity() const;

	void resolveCollision(Rigidbody* other, glm::vec2 contact, glm::vec2* collisionNormal = nullptr);

public:
	float getKineticEnergy();


protected:
	glm::vec2 m_position;
	glm::vec2 m_velocity;
	float m_mass;
	//how much the object is rotated in radians
	float m_orientation;
	float m_angularVelocity;
	// moment of inertia
	float m_moment;	
	float m_elasticity;
};

