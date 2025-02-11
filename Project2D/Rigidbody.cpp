#include "Rigidbody.h"

Rigidbody::Rigidbody(ShapeType shapeID, glm::vec2 position, glm::vec2 velocity, float orientation, float mass) 
    : PhysicsObject(shapeID), m_position (position), m_velocity (velocity), m_orientation (orientation), m_mass (mass)
{

}

Rigidbody::~Rigidbody()
{
}

void Rigidbody::fixedUpdate(glm::vec2 gravity, float timeStep)
{
    m_position += m_velocity * timeStep;
    applyForce(gravity * m_mass * timeStep);
}

void Rigidbody::applyForce(glm::vec2 force)
{
    // convert force into acceleration
    glm::vec2 acceleration = force / m_mass;
    // integrate acceleration into velocity
    m_velocity += acceleration;

}

void Rigidbody::applyForceToActor(Rigidbody* actor2, glm::vec2 force)
{
    // first check that we actor2 exists
    if (actor2 != nullptr) {
        actor2->applyForce(force);
        //apply a negative force against this object
        this->applyForce(-force);
    }
}

glm::vec2 Rigidbody::getPosition() const
{
    return m_position;
}

float Rigidbody::getOrientation() const
{
    return m_orientation;
}

glm::vec2 Rigidbody::getVelocity() const
{
    return m_velocity;
}

float Rigidbody::getMass() const
{
    return m_mass;
}
