
#include "Scene.hpp"

#include <iostream>


bool Scene::createScene()
{
	if (isCreated)
	{
		assert(false);
		std::cerr << "Scene is already created" << std::endl;
		return false;
	}

	// Do something here ...

	isCreated = true;

	return true;
}

void Scene::addPlanet(const std::shared_ptr<Planet>& planet)
{
	if (planet == nullptr)
	{
		std::cerr << "Planet is nullptr" << std::endl;
		return;
	}

	planets.push_back(planet);
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
	if (isCreated == false)
	{
		if (createScene() == false)
		{
			assert(false);
			std::cerr << "Failed to create scene" << std::endl;
			return;
		}
		isCreated = true;
	}

	// Do something here ...

}

void Scene::clear()
{
	planets.clear();
	isCreated = false;
}
