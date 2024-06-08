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

	Camera camera;

public:

	inline Camera& getCamera() { return this->camera; }

	void drawScene() const;

	inline std::shared_ptr<Scene> getScenePtr(const std::string& title) const;
	inline Scene getScene(const std::string& title) const;

	void addScene(const std::shared_ptr<Scene>& scene);

	SceneManager() {}
	virtual ~SceneManager() {}
};


#endif /* SCENEMANAGER_HPP */
