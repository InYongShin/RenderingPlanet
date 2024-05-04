
#include "Window.hpp"

void Window::clear()
{
	if (this->GLwindow) {
		glfwDestroyWindow(this->GLwindow);
		this->GLwindow = nullptr;
	}
	if (viewers.size() > 0){
		viewers.clear();
	}
}
