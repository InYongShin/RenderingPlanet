
#include "Application.hpp"
#include "SphereModel.hpp"

#include <iostream>

std::shared_ptr<Window> Application::createWindow(const std::string& title, int width, int height)
{
	std::shared_ptr<Window> pWindow(new Window(title, width, height));
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
	std::shared_ptr<Window> pWindow(createWindow("Window", 1200, 800));
	if (pWindow == nullptr)
	{
		assert(false);
		std::cerr << "Failed to create window" << std::endl;
		return;
	}

	this->window = pWindow;
}

void Application::run()
{
	if (this->window == nullptr)
	{
		assert(false);
		std::cerr << "Window is nullptr" << std::endl;
		return;
	}

	Program program("render.vert", "render.frag");

	SphereModel* sphere = new SphereModel();
	if (sphere == nullptr)
	{
		assert(false);
		std::cerr << "Failed to create spehre" << std::endl;
		return;
	}
	sphere->createSphere(0.5f, 63, 65);
	sphere->setProgram(program);

	this->window->addModel(sphere);

	this->window->display();
}