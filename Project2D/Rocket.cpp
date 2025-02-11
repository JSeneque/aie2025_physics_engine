#include "Rocket.h"

Rocket::Rocket(glm::vec2 position, glm::vec2 velocity, float mass, float radius, glm::vec4 colour, float expelledAmount) :
	Sphere(position, velocity, mass, radius, colour), m_expelledAmount{ expelledAmount }
{

}

float Rocket::getExpelledAmount() const
{
	return m_expelledAmount;
}

void Rocket::expelledFuel()
{
	if (m_mass > 0) {
		m_mass -= m_expelledAmount;
	}
}
