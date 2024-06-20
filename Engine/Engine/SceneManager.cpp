
#include "SceneManager.hpp"

inline std::shared_ptr<Scene> SceneManager::getScenePtr(const std::string& title) const
{
	for (auto& scene : this->scenes)
	{
		if (scene->getTitle().compare(title) == 0) // same
		{
			return scene;
		}
	}
	return nullptr;
}

inline Scene SceneManager::getScene(const std::string& title) const
{
	for(auto& scene : this->scenes)
	{
		if (scene->getTitle().compare(title) == 0) // same
		{
			return *scene;
		}
	}
	return Scene();
}

const std::shared_ptr<Scene>& SceneManager::findScene(const std::shared_ptr<Scene>& targetScene) const
{
	for (const auto& scene : this->scenes)
	{
		if (scene == targetScene)
		{
			return scene;
		}
	}
	return nullptr;
}

void SceneManager::addScene(const std::shared_ptr<Scene>& scene)
{
	if (scene == nullptr)
	{
		std::cerr << "Scene is nullptr" << std::endl;
		return;
	}

	this->scenes.push_back(scene);
}

void SceneManager::activateScene(const std::shared_ptr<Scene>& scene)
{
	if (scene == nullptr)
	{
		std::cerr << "Scene is nullptr" << std::endl;
		return;
	}

	std::shared_ptr<Scene> exitingScene = findScene(scene);
	if(exitingScene == nullptr)
	{
		addScene(scene);
	}

	this->activeScene = scene;
}

void SceneManager::drawScene()
{
	if (activeScene == nullptr)
	{
		if(this->scenes.size() > 0)
		{
			this->activeScene = this->scenes.front();
		}
		else
		{
			std::cerr << "No scene to draw" << std::endl;
			return;
		}
	}

	this->activeScene->drawContents();
}