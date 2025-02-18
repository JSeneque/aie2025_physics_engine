#include "Plane.h"
#include "Gizmos.h"
#include "Rigidbody.h"

Plane::Plane() : PhysicsObject(ShapeType::PLANE), m_distanceToOrigin{ 0 }, m_normal {glm::vec2(0,1)}
{
}

Plane::Plane(glm::vec2 normal, float distance) :
	PhysicsObject(ShapeType::PLANE), m_normal{normal}, m_distanceToOrigin{distance}, m_colour {glm::vec4(0,0,1,1)}
{
}

Plane::~Plane()
{
    delete this;
}

void Plane::draw()
{
    float lineSegmentLength = 300;
    glm::vec2 centerPoint = m_normal * m_distanceToOrigin;
    // easy to rotate normal through 90 degrees around z
    glm::vec2 parallel(m_normal.y, -m_normal.x);
    glm::vec4 colourFade = m_colour;
    colourFade.a = 0;
    glm::vec2 start = centerPoint + (parallel * lineSegmentLength);
    glm::vec2 end = centerPoint - (parallel * lineSegmentLength);
    //aie::Gizmos::add2DLine(start, end, colour);
    aie::Gizmos::add2DTri(start, end, start - m_normal * 10.0f, m_colour, m_colour, colourFade);
    aie::Gizmos::add2DTri(end, end - m_normal * 10.0f, start - m_normal * 10.0f, m_colour, colourFade, colourFade);
}

void Plane::resetPosition()
{
	
}

glm::vec2 Plane::getNormal()
{
	return m_normal;
}

float Plane::getDistance()
{
	return m_distanceToOrigin;
}

void Plane::resolveCollision(Rigidbody* other)
{
    glm::vec2 normal = m_normal;
    glm::vec2 relativeVelocity = other->getVelocity();

    // if the objects are already moving apart, we don't need to do anything
    if (glm::dot(normal, relativeVelocity) >= 0)
        return;

    float elasticity = 1;

    // calculate the force
    glm::vec2 force = relativeVelocity - (1 + elasticity) * relativeVelocity * normal * normal;

    // apply force to sphere
    other->applyForce(force);
}
