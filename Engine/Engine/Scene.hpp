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

	void clear();

	Scene() {}
	virtual ~Scene() {
		clear();
	}
};


#endif /* SCENE_HPP */
