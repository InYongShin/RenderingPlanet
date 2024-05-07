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

	void createScene();
	void addPlanet(const std::shared_ptr<Planet>& model);

	void drawScene() const;

	inline std::shared_ptr<Scene> getScene() const { return this->scene; }

	bool isValidScene() const { return this->scene != nullptr; }

	SceneManager() {}
	virtual ~SceneManager() {}
};


#endif /* SCENEMANAGER_HPP */
