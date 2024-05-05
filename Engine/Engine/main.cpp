
#include "Window.hpp"


int main()
{
	Window* window = new Window("Window", 1200, 800);
	window->createWindow();

	window->display();

	return 0;
}