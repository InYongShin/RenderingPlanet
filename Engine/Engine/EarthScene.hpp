#ifndef EARTHSCENE_HPP
#define EARTHSCENE_HPP

#include "Scene.hpp"

class EarthScene : public Scene
{
private:


public:
	void initialize() override;
	void update() override;

	EarthScene();
	EarthScene(const std::string& title);
	virtual ~EarthScene() {}
};


#endif /* EARTHSCENE_HPP */
