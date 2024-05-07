
#include "SceneManager.hpp"

void SceneManager::createScene()
{
	this->scene = std::make_shared<Scene>();
	if (this->scene == nullptr)
	{
		std::cerr << "Failed to create scene" << std::endl;
		return;
	}
}

void SceneManager::drawScene() const
{
	if (this->scene == nullptr)
	{
		std::cout << "Scene is nullptr. Please create scene before draw" << std::endl;
		return;
	}

	this->scene->drawContents();
}

void SceneManager::addPlanet(const std::shared_ptr<Planet>& model)
{
	if(this->scene == nullptr)
	{
		std::cout << "Scene is nullptr. Please create scene before add a model" << std::endl;
		return;
	}

	this->scene->addPlanet(model);
}
