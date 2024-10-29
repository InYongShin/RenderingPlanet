
#include "Planet.hpp"

void Planet::createPlanet(const float radius /*= 1.f*/, const glm::vec3& position /*= glm::vec3(0.f)*/, const int texID /*= -1*/, const std::string& shaderTexName /*= ""*/)
{
	if (this->sphere == nullptr)
	{
		this->sphere = std::make_shared<SphereModel>();
	}
	this->sphere->createSphere(radius);
	this->sphere->setPosition(position);
	this->sphere->addTexture(texID, shaderTexName);

	this->isCreated = true;
}

void Planet::createPlanet(const float radius, const glm::vec3& position, const int noiseWidth, const int noiseHeight, const float noiseWeight)
{
	if (this->sphere == nullptr)
	{
		this->sphere = std::make_shared<SphereModel>();
	}
	this->sphere->createSphere(radius, 63 * 3, 65 * 3, noiseWidth, noiseHeight, noiseWeight);
	this->sphere->setPosition(position);

	this->isCreated = true;
}

void Planet::setSphereProgram(const std::shared_ptr<Program>& program)
{
	if(program->isUsable() == false)
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

	for (auto& model : this->models)
	{
		model->draw();
	}
}

/*virtual*/ void Planet::update()
{
	return;

	glm::vec3 center = this->centerPosition;
	glm::vec3 position = getPosition();

	float orbitRadius = glm::length(position - center);

	double time = glfwGetTime();

	position.x = center.x + orbitRadius * cos(time) * 1.f;
	position.z = center.z + orbitRadius * sin(time) * 1.f;
	position.y = center.y;

	setPosition(position);
}

void Planet::addModel(const std::shared_ptr<Model>& model)
{
	if (model == nullptr)
	{
		std::cerr << "Model is nullptr" << std::endl;
		return;
	}

	this->models.push_back(model);
}

void Planet::addTexture(int id, const std::string& shaderName)
{
	if (this->sphere)
	{
		this->sphere->addTexture(id, shaderName);
	}
}
