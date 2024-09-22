
#include "Earth.hpp"



void Earth::update() /*override*/
{
	glm::vec3 center = this->centerPosition; // position of the sun
	glm::vec3 position = getPosition();

	float orbitRadius = glm::length(position - center);

	double time = glfwGetTime();

	position.x = center.x + orbitRadius * cos(time) * 1.f;
	position.z = center.z + orbitRadius * sin(time) * 1.f;
	position.y = center.y;

	setPosition(position);
}
