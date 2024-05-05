
#include "Window.hpp"

bool Window::initGL()
{
	if (glfwInit() == GL_FALSE)
	{
		assert(false);
		std::cerr << "Failed to initialize GLFW" << std::endl;
		return false;
	}

	int width, height;
	std::string title;
	if(this->_width>0 && this->_height>0 && this->_title.length()>0)
	{
		width = this->_width;
		height = this->_height;
		title = this->_title;
	}
	else
	{	// default values
		width = 800;
		height = 600;
		title = "Window";
	}

	this->GLwindow = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
	if (this->GLwindow == nullptr)
	{
		assert(false);
		std::cerr << "Failed to create window" << std::endl;
		glfwTerminate();
		return false;
	}
	
	glfwMakeContextCurrent(this->GLwindow);

	if (glewInit() != GLEW_OK)
	{
		assert(false);
		std::cerr << "Failed to initialize GLEW" << std::endl;
		glfwTerminate();
		return false;
	}

	std::cout << glGetString(GL_VERSION) << std::endl;

	isInitialized = true;
	return true;
}

bool Window::createWindow()
{
	if (isCreated)
	{
		assert(false);
		std::cerr << "Window is already created" << std::endl;
		return false;
	}

	if (isInitialized == false)
	{
		if (initGL() == false)
		{
			assert(false);
			std::cerr << "Failed to initialize OpenGL" << std::endl;
			return false;
		}
	}

	// TODO: How to handle scene creation?
	this->scene = new Scene();
	if (this->scene == nullptr)
	{
		assert(false);
		std::cerr << "Failed to create scene" << std::endl;
		return false;
	}

	if(scene->createScene() == false)
	{
		assert(false);
		std::cerr << "Failed to create scene" << std::endl;
		return false;
	}
	
	isCreated = true;
	return true;
}

void Window::display() const
{
	if (this->GLwindow == nullptr)
	{
		assert(false);
		std::cerr << "OpenGL window is not ready to display." << std::endl;
		return;
	}

	while (!glfwWindowShouldClose(this->GLwindow))
	{
		glClearColor(0.2f, 0.3f, 0.8f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// display something ...

		glfwSwapBuffers(this->GLwindow);
		glfwPollEvents();
	}

	glfwTerminate();
	glfwDestroyWindow(this->GLwindow);
}

void Window::clear()
{
	this->_title = "";
	this->_width = 0;
	this->_height = 0;
	this->isCreated = false;
	this->isInitialized = false;

	if (this->GLwindow) {
		glfwDestroyWindow(this->GLwindow);
		this->GLwindow = nullptr;
	}
	if (this->scene) {
		delete this->scene;
		this->scene = nullptr;
	}
}
