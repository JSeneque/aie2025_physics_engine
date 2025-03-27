#include "Sphere.h"
#include "Rigidbody.h"
#include "Gizmos.h"

Sphere::Sphere(glm::vec2 position, glm::vec2 velocity, float mass, float radius, glm::vec4 colour) :
    Rigidbody(ShapeType::SPHERE, position, velocity, 0.0f, mass, 0.0f, 1.0f)
{
    m_radius = radius;
    m_colour = colour;
    m_moment = 0.5f * mass * radius * radius;
}

Sphere::~Sphere()
{
    delete this;
}

void Sphere::draw()
{
    glm::vec2 end = glm::vec2(std::cos(m_orientation), std::sin(m_orientation)) *
        m_radius;

    aie::Gizmos::add2DCircle(m_position, m_radius, 32, m_colour);
    aie::Gizmos::add2DLine(m_position, m_position + end, glm::vec4(1, 1, 1, 1));
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
