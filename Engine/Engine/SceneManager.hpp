#ifndef SCENEMANAGER_HPP
#define	SCENEMANAGER_HPP

#include "Scene.hpp"
#include "Singleton.hpp"

#include <iostream>

class SceneManager : public Singleton<SceneManager>
{
private:
	friend class Singleton;

	std::shared_ptr<Scene> scene = nullptr;

public:

	inline std::vector<std::shared_ptr<Model>> getModels() { return this->scene->getModels(); }

	void createScene();
	void addModel(const std::shared_ptr<Model>& model);

	bool isValidScene() const { return this->scene != nullptr; }

	SceneManager() {}
	virtual ~SceneManager() {}
};


#endif /* SCENEMANAGER_HPP */
