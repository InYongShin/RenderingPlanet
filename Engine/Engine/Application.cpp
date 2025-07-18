
#include "Application.hpp"
#include "QuadModel.hpp"
#include "Texture.hpp"
#include "Light.hpp"

#include "Planet.hpp"
#include "SpaceScene.hpp"
#include "EarthScene.hpp"
#include "MySpaceScene.hpp"

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

	// std::shared_ptr<EarthScene> earthScene = std::make_shared<EarthScene>("Earth");
	// std::shared_ptr<SpaceScene> spaceScene = std::make_shared<SpaceScene>("Space");
	std::shared_ptr<MySpaceScene> mySpaceScene = std::make_shared<MySpaceScene>("MySpace");
	SceneManager::getInstance()->activateScene(mySpaceScene);
	// End set the contents

	this->window->display();
}
