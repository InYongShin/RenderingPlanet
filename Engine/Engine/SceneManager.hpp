#ifndef SCENEMANAGER_HPP
#define	SCENEMANAGER_HPP

#include "Scene.hpp"
#include "Singleton.hpp"
#include "Camera.hpp"

#include <iostream>

class SceneManager : public Singleton<SceneManager>
{
private:
	friend class Singleton;

	std::shared_ptr<Scene> scene = nullptr;

	Camera camera;

public:

	void createScene();
	void addPlanet(const std::shared_ptr<Planet>& model);

	inline Camera& getCamera() { return this->camera; }

	void drawScene() const;

	inline std::shared_ptr<Scene> getScene() const { return this->scene; }

	bool isValidScene() const { return this->scene != nullptr; }

	SceneManager() {}
	virtual ~SceneManager() {}
};


#endif /* SCENEMANAGER_HPP */
