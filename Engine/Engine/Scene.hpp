#ifndef SCENE_HPP
#define SCENE_HPP

#include "GLTools.hpp"
#include "Model.hpp"
#include "Planet.hpp"

#include <vector>
#include <iostream>

class Scene
{
private:
	bool isCreated = false;

	std::vector<std::shared_ptr<Planet>> planets;

public:

	inline std::vector<std::shared_ptr<Planet>> getPlanets() const { return planets; }

	bool createScene();

	void addPlanet(const std::shared_ptr<Planet>& planet);

	void drawContents() const;

	void run();

	void clear();

	Scene() {}
	virtual ~Scene() { clear(); }
};


#endif /* SCENE_HPP */
