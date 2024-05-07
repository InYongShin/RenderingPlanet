
#include "Scene.hpp"

#include <iostream>


bool Scene::createScene()
{
	if (this->isCreated)
	{
		assert(false);
		std::cerr << "Scene is already created" << std::endl;
		return false;
	}

	// Do something here ...

	this->isCreated = true;

	return true;
}

void Scene::addPlanet(const std::shared_ptr<Planet>& planet)
{
	if (planet == nullptr)
	{
		std::cerr << "Planet is nullptr" << std::endl;
		return;
	}

	this->planets.push_back(planet);
}

void Scene::drawContents() const
{
	for(auto& planet : this->planets)
	{
		planet->draw();
	}
}

void Scene::run()
{
	if (this->isCreated == false)
	{
		if (createScene() == false)
		{
			assert(false);
			std::cerr << "Failed to create scene" << std::endl;
			return;
		}
		this->isCreated = true;
	}

	// Do something here ...

}

void Scene::clear()
{
	this->planets.clear();
	this->isCreated = false;
}
