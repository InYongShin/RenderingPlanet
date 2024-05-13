
#include "Application.hpp"
#include "EmissivePlanet.hpp"
#include "Planet.hpp"
#include "Light.hpp"

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

	SceneManager::getInstance()->createScene();
}

void Application::run()
{
	if (this->window == nullptr || SceneManager::getInstance()->isValidScene() == false)
	{
		assert(false);
		std::cerr << "Not ready to run applicatoin" << std::endl;
		return;
	}

	SceneManager::getInstance()->getCamera().setPosition(glm::vec3(0.f, 0.f, 5.f));
	glm::mat4 viewMat = SceneManager::getInstance()->getCamera().viewMat();
	glm::mat4 projMat = SceneManager::getInstance()->getCamera().projMat();

	Program sunProgram("render.vert", "sun.frag");
	std::shared_ptr<EmissivePlanet> sun = std::make_shared<EmissivePlanet>("Sun", glm::vec3(.8f, .8f, 0.f), .5f, 1.f, sunProgram);
	sunProgram.setUniform("viewMat", viewMat);
	sunProgram.setUniform("projMat", projMat);
	SceneManager::getInstance()->addPlanet(sun);

	Program planetProgram("render.vert", "render.frag");
	std::shared_ptr<Planet> planet = std::make_shared<Planet>("Planet", glm::vec3(0.f, 0.f, 1.f), .3f, planetProgram);
	planetProgram.setUniform("viewMat", viewMat);
	planetProgram.setUniform("projMat", projMat);
	planetProgram.setUniform("lightPosition", sun->getPosition());
	planetProgram.setUniform("lightPower", sun->getEmissivePower());
	SceneManager::getInstance()->addPlanet(planet);
	
	
	this->window->display();
}
