#ifndef WINDOW_HPP
#define WINDOW_HPP

#include "Viewer.hpp"
#include "GLTools.hpp"

#include <vector>
#include <string>


class Window
{
private:
	std::string _title = "Window";
	int _width = -1;
	int _height = -1;

	GLFWwindow* GLwindow = nullptr;

	std::vector<Viewer> viewers;

public:

	inline GLFWwindow* getWindow() const { return GLwindow; }
	inline void setWindow(GLFWwindow* window) { this->GLwindow = window; }

	inline std::string getTitle() const { return _title; }
	inline int getWidth() const { return _width; }
	inline int getHeight() const { return _height; }

	void clear();

	Window() {}
	Window(const std::string& title, int width, int height)
		: _title(title), _width(width), _height(height) {}
	virtual ~Window() {
		clear();
	}
};

#endif /* WINDOW_HPP */
