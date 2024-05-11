#ifndef WINDOW_HPP
#define WINDOW_HPP

#include "GLTools.hpp"
#include "SceneManager.hpp"
#include "Scene.hpp"
#include "Camera.hpp"

#include <vector>
#include <string>


class Window
{
private:
	std::string _title = "";
	int _width = 0;
	int _height = 0;

	GLFWwindow* GLwindow = nullptr;

	Camera camera;

	bool isCreated = false;
	bool isInitialized = false;

private:
	bool initGL();

public:

	inline GLFWwindow* getWindow() const { return this->GLwindow; }
	inline void setWindow(GLFWwindow* window) { this->GLwindow = window; }

	inline std::string getTitle() const { return this->_title; }
	inline int getWidth() const { return this->_width; }
	inline int getHeight() const { return this->_height; }

	inline Camera& getCamera() { return this->camera; }

	bool isNeedCreation() const { return !this->isCreated; }
	bool isNeedInitialization() const { return !this->isInitialized; }

	bool createWindow();
	void display() const;

	void clear();

	Window() {}
	Window(const std::string& title, int width, int height)
		: _title(title), _width(width), _height(height) {}

	virtual ~Window() { clear(); }
};

#endif /* WINDOW_HPP */
