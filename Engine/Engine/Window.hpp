#ifndef WINDOW_HPP
#define WINDOW_HPP

#include "GLTools.hpp"
#include "Scene.hpp"

#include <vector>
#include <string>


class Window
{
private:
	std::string _title = "";
	int _width = 0;
	int _height = 0;

	GLFWwindow* GLwindow = nullptr;

	bool isCreated = false;
	bool isInitialized = false;

	Scene* scene = nullptr;

private:
	bool initGL();


public:

	inline GLFWwindow* getWindow() const { return GLwindow; }
	inline void setWindow(GLFWwindow* window) { this->GLwindow = window; }

	inline std::string getTitle() const { return _title; }
	inline int getWidth() const { return _width; }
	inline int getHeight() const { return _height; }

	void addModel(Model* model);

	bool createWindow();
	void display() const;

	void clear();

	Window() {}
	Window(const std::string& title, int width, int height)
		: _title(title), _width(width), _height(height) {}

	virtual ~Window() { clear(); }
};

#endif /* WINDOW_HPP */
