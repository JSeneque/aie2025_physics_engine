#pragma once

#include "Application.h"
#include "Renderer2D.h"
#include "PhysicsScene.h"

class Sphere;
class Plane;
class Stick;
class Pocket;

class Application2D : public aie::Application {
public:

	Application2D();
	virtual ~Application2D();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

protected:

	aie::Renderer2D*	m_2dRenderer;
	aie::Font*			m_font;

	PhysicsScene* m_physicsScene;

	Stick* stick;
	Sphere* cueBall;

	std::vector<Pocket> pockets;

	float m_timer;
};