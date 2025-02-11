#pragma once

#include "Application.h"
#include "Renderer2D.h"
#include "PhysicsScene.h"

class Sphere;
class Rocket;

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
	//aie::Texture*		m_texture;
	//aie::Texture*		m_shipTexture;
	aie::Font*			m_font;

	PhysicsScene* m_physicsScene;
	Sphere* ball1;
	Sphere* particle;

	Rocket* rocket;

	float m_timer;
	float m_interval;
};