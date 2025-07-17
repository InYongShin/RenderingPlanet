#ifndef MYSPACESCENE_HPP
#define MYSPACESCENE_HPP

#include "Scene.hpp"

#include <string>

class MySpaceScene : public Scene
{
private:
	std::vector<std::shared_ptr<Planet>> planets;

	void addPlanet(const std::shared_ptr<Planet>& planet);

	std::shared_ptr<Program> cloudProgram;
	std::shared_ptr<Program> oceanProgram;

public:

	inline std::vector<std::shared_ptr<Planet>> getPlanets() const { return this->planets; }

	void initialize() override;
	void update() override;

	void drawContents() const override;

	MySpaceScene();
	MySpaceScene(const std::string& title);
	virtual ~MySpaceScene();
};


#endif /* MYSPACESCENE_HPP */
