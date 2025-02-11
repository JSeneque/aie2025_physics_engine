#pragma once
#include "Sphere.h"

class Rocket :public Sphere
{
public:
	Rocket(glm::vec2 position, glm::vec2 velocity, float mass, float radius, glm::vec4 colour, float expelledAmount);
	~Rocket();

	void setExpelledAmount(float amount);
	float getExpelledAmount() const;

	void expelledFuel();

private:
	float m_expelledAmount;
};

