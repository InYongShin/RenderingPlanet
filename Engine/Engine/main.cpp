
#include "Scene.hpp"


int main()
{
	Scene* scene = new Scene();
	scene->createScene();

	scene->run();
	
	return 0;
}