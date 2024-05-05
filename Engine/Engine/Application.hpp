#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include "Window.hpp"

class Application
{
private:
	std::shared_ptr<Window> window = nullptr;

public:

	std::shared_ptr<Window> createWindow(const std::string& title, int width, int height);

	void initialize();

	void run();

	Application() {}
	virtual ~Application() {}
};


#endif /* APPLICATION_HPP */
