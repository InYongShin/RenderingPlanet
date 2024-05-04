#ifndef SCENE_HPP
#define SCENE_HPP

#include "Window.hpp"
#include "GLTools.hpp"


class Scene
{
private:
	Window* window = nullptr;

	bool initialized = false;

	bool initGL();
public:

	bool createScene();

	void run();

	Scene() {}
	virtual ~Scene() {
		if (window) {
			delete window;
			window = nullptr;
		}
	}
};


#endif /* SCENE_HPP */
