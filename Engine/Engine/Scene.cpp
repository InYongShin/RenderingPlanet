
#include "Scene.hpp"

#include <iostream>

void Scene::initialize()
{
	// ...
}

void Scene::update()
{
	// ...
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

void Scene::clear()
{
	this->planets.clear();
}
