
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

	for (auto& model : this->models)
	{
		model->draw();
	}
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
