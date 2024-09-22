
#include "Application.hpp"
#include "QuadModel.hpp"
#include "Texture.hpp"
#include "Light.hpp"

#include "EmissivePlanet.hpp"
#include "Planet.hpp"
#include "SpaceScene.hpp"
#include "EarthScene.hpp"

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


	// Start set the contents

	SceneManager::getInstance()->getCamera().setPosition(glm::vec3(0.f, 0.f, 50.f));

#if 1
	std::shared_ptr<EarthScene> earthScene = std::make_shared<EarthScene>("Earth");
	SceneManager::getInstance()->addScene(earthScene);
	SceneManager::getInstance()->activateScene(earthScene);
#else
	std::shared_ptr<SpaceScene> spaceScene = std::make_shared<SpaceScene>("Space");
	SceneManager::getInstance()->activateScene(spaceScene);
#endif

	// End set the contents


	this->window->display();
}
