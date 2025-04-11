#pragma once
#include <glm/glm.hpp>

enum ShapeType {
	PLANE = 0,
	SPHERE,
	BOX
};

class PhysicsObject
{
public:
	PhysicsObject(ShapeType shapeID, float elasticity) : m_shapeID( shapeID ) , m_elasticity( elasticity ) {}


	virtual void fixedUpdate(glm::vec2 gravity, float timeStep) = 0;
	virtual void draw() = 0;
	virtual void resetPosition() {}
	virtual ShapeType getShapeID() { return m_shapeID;  }

protected:
	ShapeType m_shapeID;
	float m_elasticity;
};

