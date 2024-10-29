#include "MySpaceScene.hpp"

#include "MyEarth.hpp"

MySpaceScene::MySpaceScene()
	: Scene()
{
}

MySpaceScene::MySpaceScene(const std::string& title)
	: Scene(title)
{
	initialize();
}

MySpaceScene::~MySpaceScene()
{
	this->planets.clear();
}

void MySpaceScene::initialize() /*override*/
{
	setBackgroundColor(glm::vec4(0.f, 0.f, 0.f, 1.f));



	std::shared_ptr<Program> myEarthProgram = std::make_shared<Program>("myearth.vert", "myearth.frag");
	
	std::shared_ptr<MyEarth> myEarth = std::make_shared<MyEarth>("MyEarth", glm::vec3(0.0f), 500.f, myEarthProgram, 200, 200, 10.0f);
	myEarthProgram->setUniform("lightPosition", glm::vec3(500.f, 500.f, 500.f));

	addPlanet(myEarth);


}

void MySpaceScene::update() /*override*/
{
	for (auto& planet : this->planets)
	{
		planet->update();
	}
}

void MySpaceScene::addPlanet(const std::shared_ptr<Planet>& planet)
{
	if (planet == nullptr)
	{
		std::cerr << "Planet is nullptr" << std::endl;
		return;
	}

	this->planets.push_back(planet);
}

void MySpaceScene::drawContents() const /*override*/
{
	for (auto& planet : this->planets)
	{
		planet->draw();
	}
}
