#ifndef SCENE_HPP
#define SCENE_HPP

#include "GLTools.hpp"
#include "Model.hpp"

#include <vector>

class Scene
{
private:
	bool isCreated = false;
	
	std::vector<std::shared_ptr<Model>> models;

public:

	inline std::vector<std::shared_ptr<Model>> getModels() { return models; }

	bool createScene();

	void addModel(const std::shared_ptr<Model>& model);

	void run();

	void clear();

	Scene() {}
	virtual ~Scene() { clear(); }
};


#endif /* SCENE_HPP */
