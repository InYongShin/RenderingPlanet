#ifndef SCENEMANAGER_HPP
#define	SCENEMANAGER_HPP

#include "Scene.hpp"
#include "Singleton.hpp"
#include "Camera.hpp"

#include <iostream>
#include <vector>

class SceneManager : public Singleton<SceneManager>
{
private:
	friend class Singleton;

	std::vector<std::shared_ptr<Scene>> scenes;
	std::shared_ptr<Scene> activeScene = nullptr;

	Camera camera;

public:

	inline Camera& getCamera() { return this->camera; }

	void updateScene();
	void drawScene();

	inline const std::shared_ptr<Scene> getScene(const std::string& title) const;
	inline const std::shared_ptr<Scene>& getActiveScene() const { return this->activeScene; }

	const std::shared_ptr<Scene>& findScene(const std::shared_ptr<Scene>& scene) const;

	void addScene(const std::shared_ptr<Scene>& scene);

	void activateScene(const std::shared_ptr<Scene>& scene);

	SceneManager() {}
	virtual ~SceneManager() {}
};


#endif /* SCENEMANAGER_HPP */
