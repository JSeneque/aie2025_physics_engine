#include "Application2D.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include "Gizmos.h"
#include "Sphere.h"
#include "Rocket.h"
#include "glm\ext.hpp"
#include <iostream>

Application2D::Application2D() {

}

Application2D::~Application2D() {
	
}

bool Application2D::startup() {
	// increase the 2d line count to maximize the number of objects we can draw
	aie::Gizmos::create(255U, 255U, 65535U, 65535U);

	m_2dRenderer = new aie::Renderer2D();
	m_font = new aie::Font("./font/consolas.ttf", 32);

	m_physicsScene = new PhysicsScene();
	m_physicsScene->setGravity(glm::vec2(0,-10));
	m_physicsScene->setTimeStep(0.01f);

	rocket = new Rocket(glm::vec2(0, -35), glm::vec2(0), 1.0f, 10, glm::vec4(1, 0, 0, 1), 0.1f);
	//ball1 = new Sphere(glm::vec2(0, -35), glm::vec2(0), 4.0f, 10, glm::vec4(1, 0, 0, 1));
	particle = new Sphere(rocket->getPosition() + glm::vec2(0,-12), glm::vec2(0), 4.0f, 1, glm::vec4(1, 1, 1, 0.75));
	
	m_physicsScene->addActor(rocket);
	m_physicsScene->addActor(particle);

	m_interval = 0.0f;

	return true;
}

void Application2D::shutdown() {
	
	//delete m_font;
	//delete m_texture;
	//delete m_shipTexture;
	//delete m_2dRenderer;
}

void Application2D::update(float deltaTime) {

	// input example
	aie::Input* input = aie::Input::getInstance();

	aie::Gizmos::clear();

	m_physicsScene->update(deltaTime);
	m_physicsScene->draw();


	m_interval += deltaTime;

	// at certain intervals, reduce the mass, spawn an other particle
	if (m_interval > 0.5f && rocket->getMass() > 0)
	{
		m_interval = 0;
		rocket->expelledFuel();
		Sphere* particle = new Sphere(rocket->getPosition() + glm::vec2(0,-12), glm::vec2(0), 4.0f, 1, glm::vec4(1, 1, 1, 0.75));
		m_physicsScene->addActor(particle);
		particle->applyForceToActor(rocket, glm::vec2(0, 2));
		
		std::cout << "Mass: " << rocket->getMass() << "\n";
	}
	
	
	
	

	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
}

void Application2D::draw() {

	// wipe the screen to the background colour
	clearScreen();

	// begin drawing sprites
	m_2dRenderer->begin();

	// draw your stuff here!
	static float aspectRatio = 16 / 9.f;
	aie::Gizmos::draw2D(glm::ortho<float>(-100, 100, -100 / aspectRatio, 100 / aspectRatio, -1.0f, 1.0f));

	m_physicsScene->draw();

	// output some text, uses the last used colour
	m_2dRenderer->drawText(m_font, "Press ESC to quit", 0, 0);
	// done drawing sprites
	m_2dRenderer->end();
}