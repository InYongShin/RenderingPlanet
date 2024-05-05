#ifndef SCENE_HPP
#define SCENE_HPP

#include "GLTools.hpp"
#include "Model.hpp"

#include <vector>

class Scene
{
private:
	bool isCreated = false;
	
	std::vector<Model*> models;

public:

	inline std::vector<Model*>& getModels() { return models; }

	bool createScene();

	void addModel(Model* model);

	void run();

	void clear();

	Scene() {}
	virtual ~Scene() { clear(); }
};


#endif /* SCENE_HPP */
