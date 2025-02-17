#pragma once

#include "Application.h"
#include "Renderer2D.h"
#include "PhysicsScene.h"

class Sphere;
class Plane;

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
	Sphere* ball1;
	Sphere* ball2;
	Sphere* ball3;
	Plane* plane1;
	Plane* plane2;

	float m_timer;
};