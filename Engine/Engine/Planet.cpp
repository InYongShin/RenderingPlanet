#include "Planet.hpp"

void Planet::createPlanet(const float radius, const glm::vec3& position, const int texID, const std::string& shaderTexName)
{
	if (this->sphere == nullptr)
	{
		this->sphere = std::make_shared<SphereModel>();
	}
	this->sphere->createSphere(radius, 63, 65);
	this->sphere->setPosition(position);
	this->sphere->addTexture(texID, shaderTexName);

	this->isCreated = true;
}

void Planet::createPlanet(const float radius, const glm::vec3& position)
{
	if (this->sphere == nullptr)
	{
		this->sphere = std::make_shared<SphereModel>();
	}
	this->sphere->createSphere(radius, 63, 65);
	this->sphere->setPosition(position);

	this->isCreated = true;

}

void Planet::createPlanet(const float radius, const glm::vec3& position, const int noiseWidth, const int noiseHeight, const float noiseWeight)
{
	if (this->sphere == nullptr)
	{
		this->sphere = std::make_shared<SphereModel>();
	}
	this->sphere->createSphere(radius, 63 * 3, 65 * 3, noiseWeight);
	this->sphere->setPosition(position);

	this->isCreated = true;
}

void Planet::createPlanet(const float radius, const glm::vec3& position, const int resolution)
{
	if (this->sphere == nullptr)
	{
		this->sphere = std::make_shared<SphereModel>();
	}
	this->sphere->createSphere(radius, resolution);
	this->sphere->setPosition(position);

	this->isCreated = true;
}

void Planet::setRenderPass(const std::shared_ptr<RenderPass>& renderPass)
{
	if (renderPass == nullptr)
	{
		std::cerr << "RenderPass is nullptr" << std::endl;
		return;
	}

	if (this->sphere == nullptr)
	{
		std::cerr << "Sphere is nullptr" << std::endl;
		return;
	}

	// this->sphere->setRenderPass(renderPass);
}

void Planet::draw() const
{
	if (this->sphere)
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
