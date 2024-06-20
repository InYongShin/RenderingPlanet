#ifndef SPACESCENE_HPP
#define SPACESCENE_HPP

#include "Scene.hpp"

#include <string>

class SpaceScene : public Scene
{
private:

public:

	void initialize() override;
	void update() override;

	SpaceScene();
	SpaceScene(const std::string& title);
	virtual ~SpaceScene() {}
};


#endif /* SPACESCENE_HPP */
