
#include "Window.hpp"

bool Window::initGL()
{
	// TODO: How to initialize OpenGL?
	// It is not that good to initialize OpenGL in Window class.

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

	SceneManager::getInstance()->getCamera().setViewport({width, height});

	setCallbackFunc();

	this->isInitialized = true;
	return true;
}

bool Window::createWindow()
{
	if (this->isCreated)
	{
		assert(false);
		std::cerr << "Window is already created" << std::endl;
		return false;
	}

	if (this->isInitialized == false)
	{
		if (initGL() == false)
		{
			assert(false);
			std::cerr << "Failed to initialize OpenGL" << std::endl;
			return false;
		}
	}
	
	this->isCreated = true;
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

	const glm::vec4& bgColor = SceneManager::getInstance()->getActiveScene()->getBackgroundColor();

	while (!glfwWindowShouldClose(this->GLwindow))
	{
		glClearColor(bgColor.r, bgColor.g, bgColor.b, bgColor.a);

		int w=0, h=0;
		glfwGetWindowSize(this->GLwindow, &w, &h);
		glViewport(0, 0, w, h);

		SceneManager::getInstance()->getCamera().setViewport({ w, h });
		SceneManager::getInstance()->updateScene();
		// SceneManager::getInstance()->drawScene();

		RenderManager::getInstance()->render();

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
}
