
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
	
}
