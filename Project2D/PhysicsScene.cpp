#include "PhysicsScene.h"
#include "PhysicsObject.h"
#include "Sphere.h"
#include "Plane.h"

PhysicsScene::PhysicsScene() : m_timeStep{ 0.01f }, m_gravity{glm::vec2(0,0)}
{

}

PhysicsScene::~PhysicsScene()
{
	for (auto pActor : m_actors)
	{
		delete pActor;
	}
}

void PhysicsScene::addActor(PhysicsObject* actor)
{
	m_actors.push_back(actor);
}

void PhysicsScene::removeActor(PhysicsObject* actor)
{
	auto it = find(m_actors.begin(), m_actors.end(), actor);

	// if we find the actor in the vector, remove it
	// TODO: Maybe I can do this with checking first
	if (it != m_actors.end())
	{
		m_actors.erase(find(m_actors.begin(), m_actors.end(), actor));
	}
}

// function pointer array for doing our collsions
typedef bool(*fn)(PhysicsObject*, PhysicsObject*);

static fn collisionFunctionArray[] =
{
	PhysicsScene::plane2Plane, PhysicsScene::plane2Sphere,
	PhysicsScene::sphere2Plane, PhysicsScene::sphere2Sphere,
};

void PhysicsScene::update(float dt)
{
	// update physics at a fixed time step
	static float accumulatedTime = 0.0f;
	accumulatedTime += dt;

	while (accumulatedTime >= m_timeStep)
	{
		for (auto pActor : m_actors)
		{
			pActor->fixedUpdate(m_gravity, m_timeStep);
		}

		accumulatedTime -= m_timeStep;

		// check for collisions (ideally you'd want to have some sort of 
		// scene management in place)
		int actorCount = m_actors.size();

		// need to check for collisions against all objects except this one.
		for (int outer = 0; outer < actorCount - 1; outer++)
		{
			for (int inner = outer + 1; inner < actorCount; inner++)
			{
				PhysicsObject* object1 = m_actors[outer];
				PhysicsObject* object2 = m_actors[inner];
				int shapeId1 = object1->getShapeID();
				int shapeId2 = object2->getShapeID();

				// using function pointers
				int functionIdx = (shapeId1 * SHAPE_COUNT) + shapeId2;
				fn collisionFunctionPtr = collisionFunctionArray[functionIdx];
				if (collisionFunctionPtr != nullptr)
				{
					// did a collision occur?
					collisionFunctionPtr(object1, object2);
				}
			}
		}
	}
}

void PhysicsScene::draw()
{
	for (auto pActor : m_actors)
	{
		pActor->draw();
	}
}

void PhysicsScene::setGravity(const glm::vec2 gravity)
{
	m_gravity = gravity;
}

glm::vec2 PhysicsScene::getGravity() const
{
	return m_gravity;
}

void PhysicsScene::setTimeStep(const float timeStep)
{
	m_timeStep = timeStep;
}

float PhysicsScene::getTimeStep() const
{
	return m_timeStep;
}

bool PhysicsScene::sphere2Sphere(PhysicsObject* obj1, PhysicsObject* obj2)
{
	// try to cast objects to sphere and sphere
	Sphere* sphere1 = dynamic_cast<Sphere*>(obj1);
	Sphere* sphere2 = dynamic_cast<Sphere*>(obj2);
	// if we are successful then test for collision
	if (sphere1 != nullptr && sphere2 != nullptr)
	{
		// TODO do the necessary maths in here
		// compare the distance between their centres and if smaller than the sum of their radius,
		// then they have collided
		if (glm::distance(sphere1->getPosition(), sphere2->getPosition()) 
			< (sphere1->getRadius() + sphere2->getRadius()))
		{
			// TODO if the spheres touch, set their velocities to zero for now
			sphere1->setVelocity(glm::vec2(0, 0));
			sphere2->setVelocity(glm::vec2(0, 0));
		}
		
	}

	return false;
}

bool PhysicsScene::sphere2Plane(PhysicsObject* obj1, PhysicsObject* obj2)
{
	Sphere* sphere = dynamic_cast<Sphere*>(obj1); 
	Plane* plane = dynamic_cast<Plane*>(obj2);

	//if we are successful then test for collision
	if (sphere != nullptr && plane != nullptr)
	{
		// get the normal for the plane
		glm::vec2 collisionNormal = plane->getNormal();
		float sphereToPlane = glm::dot(sphere->getPosition(), plane->getNormal()) - plane->getDistance();

		float intersection = sphere->getRadius() - sphereToPlane;
		float velocityOutOfPlane = glm::dot(sphere->getVelocity(), plane->getNormal());
		if (intersection > 0 && velocityOutOfPlane < 0)
		{
			//set sphere velocity to zero here
			sphere->applyForce(-sphere->getVelocity() * sphere->getMass());
			return true;
		}
	}

	return false;
}

bool PhysicsScene::plane2Plane(PhysicsObject* obj1, PhysicsObject* obj2)
{
	return false;
}

bool PhysicsScene::plane2Sphere(PhysicsObject* obj1, PhysicsObject* obj2)
{
	// reverse the order of arguments, as obj1 is the plane and obj2 is the sphere
	return sphere2Plane(obj2, obj1);
}


