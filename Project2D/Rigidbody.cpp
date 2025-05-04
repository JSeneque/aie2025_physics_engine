#include "Rigidbody.h"
#include <iostream> 

Rigidbody::Rigidbody(ShapeType shapeID, glm::vec2 position, glm::vec2 velocity, float orientation, float mass,
    float angularVelocity, float elasticity)
    : PhysicsObject(shapeID, elasticity), m_position (position), m_velocity (velocity), m_orientation (orientation), m_mass (mass),
    m_angularVelocity (angularVelocity), m_linearDrag{0.3f}, m_angularDrag{0.3f}
{
    
}

Rigidbody::~Rigidbody()
{
}

void Rigidbody::fixedUpdate(glm::vec2 gravity, float timeStep)
{
    m_velocity -= m_velocity * m_linearDrag * timeStep;
    m_angularVelocity -= m_angularVelocity * m_angularDrag * timeStep;

    if (length(m_velocity) < MIN_LINEAR_THRESHOLD) {
        m_velocity = glm::vec2(0, 0);
    }
    if (abs(m_angularVelocity) < MIN_ANGULAR_THRESHOLD)
    {
        m_angularVelocity = 0;
    }
    
    // move to new position
    m_position += getVelocity()  * timeStep;
    
    // apply gravity
    applyForce(gravity * getMass() *  timeStep);

    // update rotation according to the angular velocty
    m_orientation += m_angularVelocity * timeStep;
    //m_orientation += m_angularVelocity * m_angularDrag* timeStep;


}

void Rigidbody::applyForce(glm::vec2 force, glm::vec2 pos)
{
    // calculate velocity by adding acceleration
    m_velocity += force / getMass();
    m_angularVelocity += (force.y * pos.x - force.x * pos.y) / getMoment();
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

float Rigidbody::getMoment() const
{
    return m_moment;
}

float Rigidbody::getElasticity() const
{
    return m_elasticity;
}

float Rigidbody::getAngularVelocity() const
{
    return m_angularVelocity;
}

float Rigidbody::getKineticEnergy()
{
    return 0.5f * (m_mass * glm::dot(m_velocity, m_velocity) +
        m_moment * m_angularVelocity * m_angularVelocity);
}


void Rigidbody::resolveCollision(Rigidbody* other, glm::vec2 contact, glm::vec2* collisionNormal)
{
    // find the vector between their centres, or use the provided direction
    // of force, and make sure its normalised
    glm::vec2 normal = glm::normalize(collisionNormal ? *collisionNormal : 
        other->getPosition() - this->m_position);
    // get the vector perpendicular to the collision normal
    glm::vec2 perp(normal.y, -normal.x);

    float elasticity = (getElasticity() + other->getElasticity()) / 2.0f;

    // r is the radius from axis to application of force
    float r1 = glm::dot(contact - m_position, -perp);
    float r2 = glm::dot(contact - other->getPosition(), perp);
    // velocity of the contact point on this object
    float v1 = glm::dot(m_velocity, normal) - r1 * m_angularVelocity;
    // velocity of the contact on other actor
    float v2 = glm::dot(other->getVelocity(), normal) + r2 * other->getAngularVelocity();

    // check they are moving closer
    if (v1 > v2)
    {
        // calculate the effective mass at contact point for each object
        // this is how much the contact point will move due to the force applied
        float mass1 = 1.0f / (1.0f / m_mass + (r1 * r1) / m_moment);
        float mass2 = 1.0f / (1.0f / other->getMass() + (r2 * r2) / other->getMoment());

        //float elasticity = 1;

        glm::vec2 force = (1.0f + elasticity) * mass1 * mass2 /
            (mass1 + mass2) * (v1 - v2) * normal;

        // apply equal and possible forces
        applyForce(-force, contact - m_position);
        other->applyForce(force, contact - other->getPosition());
    }
}

float Rigidbody::GetLinearDrag() const
{
    return m_linearDrag;
}

float Rigidbody::GetAngularDrag() const
{
    return m_angularDrag;
}

void Rigidbody::SetLinearDrag(float linearDrag)
{
    m_linearDrag = linearDrag;
}

void Rigidbody::SetAngularDrag(float angularDrag)
{
    m_angularDrag = angularDrag;
}




