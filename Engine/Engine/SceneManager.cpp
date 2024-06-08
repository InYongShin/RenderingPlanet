
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

void SceneManager::drawScene() const
{
	for (auto& scene : this->scenes)
	{
		scene->drawContents();
	}
}