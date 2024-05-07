
#include "Planet.hpp"

void Planet::createPlanet(const float radius)
{
	if (this->sphere == nullptr)
	{
		this->sphere = std::make_shared<SphereModel>();
	}
	this->sphere->createSphere(radius);

	isCreated = true;
}

void Planet::setSphereProgram(const Program& program)
{
	if(program.isUsable() == false)
	{
		std::cerr << "Program is not usable" << std::endl;
		return;
	}

	if (this->sphere)
	{
		this->sphere->setProgram(program);
	}
}

void Planet::draw() const
{
	if(this->sphere)
	{
		this->sphere->draw();
	}

	// draw other objects ...
}
