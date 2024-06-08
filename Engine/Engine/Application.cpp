
#include "Application.hpp"
#include "EmissivePlanet.hpp"
#include "Planet.hpp"
#include "Light.hpp"
#include "SpaceScene.hpp"
#include "QuadModel.hpp"
#include "Texture.hpp"

#include <iostream>

std::shared_ptr<Window> Application::createWindow(const std::string& title, int width, int height)
{
	std::shared_ptr<Window> pWindow = std::make_shared<Window>(title, width, height);
	if (pWindow == nullptr)
	{
		assert(false);
		std::cerr << "Failed to create window" << std::endl;
		return nullptr;
	}

	pWindow->createWindow();

	return pWindow;
}

void Application::initialize()
{
	this->window = createWindow("Window", 1200, 800);
	if (this->window == nullptr)
	{
		assert(false);
		std::cerr << "Failed to create window" << std::endl;
		return;
	}
}

void Application::run()
{
	if (this->window == nullptr)
	{
		assert(false);
		std::cerr << "Not ready to run applicatoin" << std::endl;
		return;
	}


	// Start set the world contents

	SceneManager::getInstance()->getCamera().setPosition(glm::vec3(0.f, 0.f, 5.f));

	
	std::shared_ptr<SpaceScene> spaceScene = std::make_shared<SpaceScene>();


	Program sunProgram("render.vert", "texture.frag");
	Texture sunTexture("../Textures/Sun.jpg");
	sunTexture.bind(1, sunProgram, "tex");
	std::shared_ptr<EmissivePlanet> sun = std::make_shared<EmissivePlanet>("Sun", glm::vec3(-12.f, 0.f, 0.f), 10.9f, 1.f, sunProgram);
	spaceScene->addPlanet(sun);

	Program mercuryProgram("render.vert", "render.frag");
	Texture mercuryTexture("../Textures/Mercury.jpg");
	mercuryTexture.bind(2, mercuryProgram, "tex");
	std::shared_ptr<Planet> mercury = std::make_shared<Planet>("Mercury", glm::vec3(-0.61f, 0.f, 0.f), 0.04f, mercuryProgram);
	mercuryProgram.setUniform("lightPosition", sun->getPosition());
	mercuryProgram.setUniform("lightPower", sun->getEmissivePower());
	spaceScene->addPlanet(mercury);

	Program venusProgram("render.vert", "render.frag");
	Texture venusTexture("../Textures/Venus.jpg");
	venusTexture.bind(3, venusProgram, "tex");
	std::shared_ptr<Planet> venus = std::make_shared<Planet>("Venus", glm::vec3(-0.28f, 0.f, 0.f), .09f, venusProgram);
	venusProgram.setUniform("lightPosition", sun->getPosition());
	venusProgram.setUniform("lightPower", sun->getEmissivePower());
	spaceScene->addPlanet(venus);

	Program earthProgram("render.vert", "render.frag");
	Texture earthTexture("../Textures/Earth.jpg");
	earthTexture.bind(4, earthProgram, "tex");
	std::shared_ptr<Planet> earth = std::make_shared<Planet>("Earth", glm::vec3(0.f, 0.f, 0.f), 0.1f, earthProgram);
	earthProgram.setUniform("lightPosition", sun->getPosition());
	earthProgram.setUniform("lightPower", sun->getEmissivePower());
	spaceScene->addPlanet(earth);

	Program earthTextProgram("render.vert", "texture.frag");
	Texture earthTextTexture("../Textures/Earth Text.png");
	earthTextTexture.bind(11, earthTextProgram, "tex");
	std::shared_ptr<QuadModel> earthTextQuad = std::make_shared<QuadModel>();
	glm::vec3 lt = glm::vec3(earth->getPosition() + glm::vec3(-earth->getRadius(), earth->getRadius() * 2.2f, 0.f));
	glm::vec3 rb = glm::vec3(earth->getPosition() + glm::vec3( earth->getRadius(), earth->getRadius() * 1.2f, 0.f));
	earthTextQuad->createQuad(lt, rb);
	earthTextQuad->setProgram(earthTextProgram);
	earth->addModel(earthTextQuad);

	Program moonProgram("render.vert", "render.frag");
	Texture moonTexture("../Textures/Moon.jpg");
	moonTexture.bind(5, moonProgram, "tex");
	std::shared_ptr<Planet> moon = std::make_shared<Planet>("Moon", glm::vec3(.15f, 0.f, 0.f), 0.025f, moonProgram);
	moonProgram.setUniform("lightPosition", sun->getPosition());
	moonProgram.setUniform("lightPower", sun->getEmissivePower());
	spaceScene->addPlanet(moon);

	Program marsProgram("render.vert", "render.frag");
	Texture marsTexture("../Textures/Mars.jpg");
	marsTexture.bind(6, marsProgram, "tex");
	std::shared_ptr<Planet> mars = std::make_shared<Planet>("Mars", glm::vec3(0.52f, 0.f, 0.f), .05f, marsProgram);
	marsProgram.setUniform("lightPosition", sun->getPosition());
	marsProgram.setUniform("lightPower", sun->getEmissivePower());
	spaceScene->addPlanet(mars);

	Program jupiterProgram("render.vert", "render.frag");
	Texture jupiterTexture("../Textures/Jupiter.jpg");
	jupiterTexture.bind(7, jupiterProgram, "tex");
	std::shared_ptr<Planet> jupiter = std::make_shared<Planet>("Jupiter", glm::vec3(4.2f, 0.f, 0.f), 1.12f, jupiterProgram);
	jupiterProgram.setUniform("lightPosition", sun->getPosition());
	jupiterProgram.setUniform("lightPower", sun->getEmissivePower());
	spaceScene->addPlanet(jupiter);

	Program saturnProgram("render.vert", "render.frag");
	Texture saturnTexture("../Textures/Saturn.jpg");
	saturnTexture.bind(8, saturnProgram, "tex");
	std::shared_ptr<Planet> saturn = std::make_shared<Planet>("Saturn", glm::vec3(8.52f, 0.f, 0.f), 0.94f, saturnProgram);
	saturnProgram.setUniform("lightPosition", sun->getPosition());
	saturnProgram.setUniform("lightPower", sun->getEmissivePower());
	spaceScene->addPlanet(saturn);

	Program uranusProgram("render.vert", "render.frag");
	Texture uranusTexture("../Textures/Uranus.jpg");
	uranusTexture.bind(9, uranusProgram, "tex");
	std::shared_ptr<Planet> uranus = std::make_shared<Planet>("Uranus", glm::vec3(18.21f, 0.f, 0.f), 0.4f, uranusProgram);
	uranusProgram.setUniform("lightPosition", sun->getPosition());
	uranusProgram.setUniform("lightPower", sun->getEmissivePower());
	spaceScene->addPlanet(uranus);

	Program neptuneProgram("render.vert", "render.frag");
	Texture neptuneTexture("../Textures/Neptune.jpg");
	neptuneTexture.bind(10, neptuneProgram, "tex");
	std::shared_ptr<Planet> neptune = std::make_shared<Planet>("Neptune", glm::vec3(29.07f, 0.f, 0.f), 0.39f, neptuneProgram);
	neptuneProgram.setUniform("lightPosition", sun->getPosition());
	neptuneProgram.setUniform("lightPower", sun->getEmissivePower());
	spaceScene->addPlanet(neptune);


	SceneManager::getInstance()->addScene(spaceScene);
	
	// End set the world contents


	this->window->display();
}
