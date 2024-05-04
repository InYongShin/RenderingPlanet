
#include "Scene.hpp"

#include <iostream>


bool Scene::createScene()
{
	if (initialized)
	{
		assert(false);
		std::cerr << "Scene is already initialized" << std::endl;
		return false;
	}

	// TODO: How to handle creating Window class?
	this->window = new Window();

	if(initGL() == false)
	{
		assert(false);
		std::cerr << "Failed to create scene" << std::endl;
		return false;
	}


	return true;
}

bool Scene::initGL()
{
	if (!glfwInit())
	{
		assert(false);
		std::cerr << "Failed to initialize GLFW" << std::endl;
		return false;
	}

	GLFWwindow* window = glfwCreateWindow(800, 600, "Window", nullptr, nullptr);
	if (window == nullptr)
	{
		assert(false);
		std::cerr << "Failed to create window" << std::endl;
		glfwTerminate();
		return false;
	}

	glfwMakeContextCurrent(window);

	if (glewInit() != GLEW_OK)
	{
		assert(false);
		std::cerr << "Failed to initialize GLEW" << std::endl;
		glfwTerminate();
		return false;
	}

	std::cout << glGetString(GL_VERSION) << std::endl;

	// TODO: How to handle setting window?
	this->window->setWindow(window);

	initialized = true;
	return true;
}

void Scene::run()
{
	if (initialized == false)
	{
		assert(false);
		std::cerr << "Scene is not initialized" << std::endl;
		return;
	}

	GLFWwindow* window = this->window->getWindow();
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.2f, 0.3f, 0.8f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	glfwDestroyWindow(window);
}
