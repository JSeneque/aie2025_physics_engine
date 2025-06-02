#include "Application2D.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include "Gizmos.h"
#include "Sphere.h"
#include "Plane.h"
#include "Box.h"
#include "glm\ext.hpp"
#include "Stick.h"
#include "Pocket.h"
#include "Ball.h"
#include <iostream>

#include "gl_core_4_4.h"


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
	m_physicsScene->setGravity(glm::vec2(0.0f, 0.0f));
	m_physicsScene->setTimeStep(0.01f);

	/*Sphere* ball1 = new Sphere(glm::vec2(9, 25), glm::vec2(0,1), 4.0f, 4, glm::vec4(1, 0, 0, 1), 0.8f);
	Sphere* ball2 = new Sphere(glm::vec2(5, 40), glm::vec2(10,1), 4.0f, 4, glm::vec4(0, 1, 0, 1), 0.8f);
	Plane* plane1 = new Plane(glm::vec2(0, 1), -20, 0.1f);		// Horizontal
	Plane* plane2 = new Plane(glm::vec2(1, 0), -30, 0.1f);			// Vertical
	Plane* plane3 = new Plane(glm::vec2(-1, 0), -30, 0.1f);	
	Box* box1 = new Box(glm::vec2(0, -7), glm::vec2(0, 1), 4.0f, glm::vec2(8, 3), glm::vec4(0.5f, 0.5f, 0.5f, 1), 0, 0.8f);
	Box* box2 = new Box(glm::vec2(-7, 20), glm::vec2(0, 1), 4.0f, glm::vec2(4, 4), glm::vec4(1, 1, 0, 1), 0, 0.8f);*/

	/*box1->SetKinematic(true);

	ball1->SetLinearDrag(0.3f);
	ball2->SetLinearDrag(0.3f);
	ball1->SetAngularDrag(0.3f);
	ball2->SetAngularDrag(0.3f);

	m_physicsScene->addActor(ball1);
	m_physicsScene->addActor(ball2);
	m_physicsScene->addActor(plane1);
	m_physicsScene->addActor(plane2);
	m_physicsScene->addActor(plane3);
	m_physicsScene->addActor(box1);
	m_physicsScene->addActor(box2);*/


	// balls setup
	glm::vec2 rackOrigin =  {17.0f, 0.0f};

	float ballRadius = 1.5f;
	float ballDiameter = ballRadius * 2.0f;
	float rowSpacing = ballDiameter;						// Horizontal distance between balls in a row
	float colSpacing = ballDiameter * sqrt(3) / 2.0f;	// Vertical offset (60° triangle)
	
	int ballIndex = 0;
	for (int row = 0; row < 5; ++row)
	{
		for (int i = 0; i <= row; ++i)
		{
			//Sphere* ball = new Sphere({0,0}, {0,0},4,ballRadius, {1,0,0,1}, 1);
			Ball* ball = new Ball({0,0}, {0,0},4,ballRadius, {1,0,0,1}, 1);
			float x = rackOrigin.x + row * rowSpacing;
			float y = rackOrigin.y - row * colSpacing / 2.0f + i * colSpacing;

			ball->SetPosition({x,y});

			ball->SetLinearDrag(0.3f);
			ball->SetAngularDrag(0.3f);
			
			//balls.push_back(ball);

			m_physicsScene->addActor(ball);
		}
	}
	int tableWidth = 40;
	int tableHeight = 20;
	// table setup
	Box* topBoundary = new Box(glm::vec2(0, 20), glm::vec2(0, 1), 4.0f, glm::vec2(tableWidth, 2), glm::vec4(0.0f, 0.51f, 0.0f, 1), 0, 0.8f);
	Box* leftBoundary = new Box(glm::vec2(-39, 0), glm::vec2(0, 1), 4.0f, glm::vec2(2, tableHeight + 2), glm::vec4(0.0f, 0.51f, 0.0f, 1), 0, 0.8f);
	Box* bottomBoundary = new Box(glm::vec2(0, -20), glm::vec2(0, 1), 4.0f, glm::vec2(tableWidth, 2), glm::vec4(0.0f, 0.51f, 0.0f, 1), 0, 0.8f);
	Box* rightBoundary = new Box(glm::vec2(39, 0), glm::vec2(0, 1), 4.0f, glm::vec2(2, tableHeight + 2), glm::vec4(0.0f, 0.51f, 0.0f, 1), 0, 0.8f);
	
	topBoundary->SetKinematic(true);
	rightBoundary->SetKinematic(true);
	bottomBoundary->SetKinematic(true);
	leftBoundary->SetKinematic(true);
		
	m_physicsScene->addActor(topBoundary);
	m_physicsScene->addActor(rightBoundary);
	m_physicsScene->addActor(bottomBoundary);
	m_physicsScene->addActor(leftBoundary);
 
	// table pockets
	pockets.push_back({{tableWidth - 3, tableHeight - 2}, 3.0f});
	pockets.push_back({{- tableWidth + 3, tableHeight - 2}, 3.0f});
	pockets.push_back({{tableWidth - 3, -tableHeight + 2}, 3.0f});
	pockets.push_back({{- tableWidth + 3, -tableHeight + 2}, 3.0f});
	pockets.push_back({{0, -tableHeight + 2}, 3.0f});
	pockets.push_back({{0, tableHeight - 2}, 3.0f});
	
	// setup cue ball

	cueBall = new Sphere({-25,0}, {0,0},4,ballRadius, {1,1,1,1}, 1);

	cueBall->SetLinearDrag(0.3f);
	cueBall->SetAngularDrag(0.3f);
	
	m_physicsScene->addActor(cueBall);

	// stick
	stick = new Stick(cueBall->getPosition());
	
	return true;
}

void Application2D::shutdown() {
	
}

void Application2D::update(float deltaTime) {

	// input example
	aie::Input* input = aie::Input::getInstance();

	aie::Gizmos::clear();

	m_physicsScene->update(deltaTime);
	m_physicsScene->draw();

	stick->Update(deltaTime);
	
	// when a ball is pocketed
	std::vector<PhysicsObject*> toRemove;
	auto& actors = m_physicsScene->getActors();

	for (auto& actor : actors)
	{
		Ball* ball = dynamic_cast<Ball*>(actor);
		if (!ball || ball->IsPocketed())
		{
			Sphere* sphere = dynamic_cast<Sphere*>(actor);

			// check if cue ball because it is a sphere and white
			// could improve with a cue ball class
			if (sphere && sphere->getColour() == glm::vec4(1.0f))
			{
				if (sphere->getVelocity() == glm::vec2(0.0f))
				{
					stick->SetPosition(sphere->getPosition());
				}
			}
			continue;
		}

		for (auto& pocket : pockets)
		{
			if (ball->IsInPocket(pocket)) {
				ball->setVelocity({0, 0});
				ball->SetKinematic(true);
				ball->SetPocketed(true);

				toRemove.push_back(ball);
				std::cout << "Ball pocketed!" << std::endl;
				break;
				
			}
		}
	}

	// now remove the pocketed balls
	for (auto& actor : toRemove)
	{
		m_physicsScene->removeActor(actor);
	}
	
	

	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
	if (input->isKeyDown(aie::INPUT_KEY_SPACE))
		cueBall->setVelocity(stick->GetDirection() * stick->GetPower());
}

void Application2D::draw() {

	// wipe the screen to the background colour
	clearScreen();

	// begin drawing sprites
	m_2dRenderer->begin();
	
	for (auto& pocket : pockets) {
		pocket.Draw();
	}

	stick->Draw();
	stick->DrawImGui();
	static float aspectRatio = 16 / 9.f;
	aie::Gizmos::draw2D(glm::ortho<float>(-100, 100, -100 / aspectRatio, 100 / aspectRatio, -1.0f, 1.0f));

	

	// output some text, uses the last used colour
	m_2dRenderer->drawText(m_font, "Press ESC to quit", 0, 0);
	// done drawing sprites
	m_2dRenderer->end();
}