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
	std::string _title = "";

	std::vector<std::shared_ptr<Planet>> planets;

public:

	inline std::vector<std::shared_ptr<Planet>> getPlanets() const { return this->planets; }

	inline std::string getTitle() const { return this->_title; }

	void addPlanet(const std::shared_ptr<Planet>& planet);

	void drawContents() const;

	void clear();

	Scene() {}
	Scene(const std::string& title) : _title(title) {}
	virtual ~Scene() { clear(); }
};


#endif /* SCENE_HPP */
