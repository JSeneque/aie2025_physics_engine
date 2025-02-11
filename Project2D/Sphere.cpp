#include "Sphere.h"
#include "Rigidbody.h"
#include "Gizmos.h"

Sphere::Sphere(glm::vec2 position, glm::vec2 velocity, float mass, float radius, glm::vec4 colour) :
    Rigidbody(SPHERE, position, velocity, 0.0f, mass)
{
    m_radius = radius;
    m_colour = colour;
}

Sphere::~Sphere()
{
}

void Sphere::draw()
{
    aie::Gizmos::add2DCircle(m_position, m_radius, 32, m_colour);
}

float Sphere::getRadius() const
{
    return m_radius;
}

glm::vec4 Sphere::getColour() const
{
    return m_colour;
}

void Sphere::setVelocity(glm::vec2 value)
{
    m_velocity = value;
}
