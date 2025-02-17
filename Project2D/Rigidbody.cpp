#include "Rigidbody.h"
#include <iostream> 

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
    // integrate acceleration into velocityf
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

float Rigidbody::getKineticEnergy()
{
    // Retrieve the object's mass
    float mass = getMass();
    // Retrieve the object's velocity
    glm::vec2 velocity = getVelocity();

    float speedSquared = glm::dot(velocity, velocity); // Equivalent to v^2

    return 0.5f * mass * speedSquared;
}

void Rigidbody::resolveCollision(Rigidbody* other)
{
    glm::vec2 normal = glm::normalize(other->getPosition() - this->m_position);
    glm::vec2 relativeVelocity = other->getVelocity() - this->m_velocity;

    // if the objects are already moving apart, we don't need to do anything
    if (glm::dot(normal, relativeVelocity) >= 0)
        return;

    float elasticity = 1;
    float j = glm::dot(-(1 + elasticity) * (relativeVelocity), normal) /
                            ((1 / m_mass) + (1 / other->getMass()));

    glm::vec2 force = normal * j;

    float kePre = this->getKineticEnergy() + other->getKineticEnergy();

    this->applyForceToActor(other, force);

    float kePost = this->getKineticEnergy() + other->getKineticEnergy();

    float deltaKE = kePost - kePre;
    if (deltaKE > kePost - kePre)
        std::cout << "Kinetic Energy discrepancy greater than 1% detected!";
}




