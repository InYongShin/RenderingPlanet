
#include "Application.hpp"
#include "Planet.hpp"

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

	Program program("render.vert", "render.frag");

	std::shared_ptr<Planet> planet = std::make_shared<Planet>("Planet", .7f, program);
	if (planet == nullptr)
	{
		std::cerr << "Failed to create spehre" << std::endl;
		return;
	}

	SceneManager::getInstance()->addPlanet(planet);
	
	this->window->display();
}
