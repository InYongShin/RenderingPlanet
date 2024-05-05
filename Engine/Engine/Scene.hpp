#ifndef SCENE_HPP
#define SCENE_HPP

#include "GLTools.hpp"


class Scene
{
private:
	bool isCreated = false;
	
public:

	bool createScene();

	void run();

	void clear();

	Scene() {}
	virtual ~Scene() { clear(); }
};


#endif /* SCENE_HPP */
