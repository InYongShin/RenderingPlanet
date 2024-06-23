#ifndef SPACESCENE_HPP
#define SPACESCENE_HPP

#include "Scene.hpp"

#include <string>

class SpaceScene : public Scene
{
private:

	std::vector<std::shared_ptr<Planet>> planets;

	void addPlanet(const std::shared_ptr<Planet>& planet);

public:

	inline std::vector<std::shared_ptr<Planet>> getPlanets() const { return this->planets; }

	void initialize() override;
	void update() override;

	void drawContents() const override;

	SpaceScene();
	SpaceScene(const std::string& title);
	virtual ~SpaceScene();
};


#endif /* SPACESCENE_HPP */
