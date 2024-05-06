
#include "SceneManager.hpp"

void SceneManager::createScene()
{
	this->scene = std::make_shared<Scene>();
	if (this->scene == nullptr)
	{
		assert(false);
		std::cerr << "Failed to create scene" << std::endl;
	}
}

void SceneManager::addModel(const std::shared_ptr<Model>& model)
{
	if(this->scene == nullptr)
	{
		std::cout << "Scene is nullptr. Please create scene before add a model" << std::endl;
		return;
	}

	this->scene->addModel(model);
}
