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

	const glm::vec3& lightPosition = glm::vec3(500.f, 500.f, 500.f);
	const float earthRadius = 10.0f;

	std::shared_ptr<Program> myEarthProgram = std::make_shared<Program>("myearth.vert", "myearth.frag");
	std::shared_ptr<MyEarth> myEarth = std::make_shared<MyEarth>("MyEarth", glm::vec3(0.0f), earthRadius, 100, myEarthProgram);
	myEarthProgram->setUniform("lightPosition", lightPosition);

	std::shared_ptr<Program> oceanProgram = std::make_shared<Program>("ocean.vert", "ocean.frag");
	std::shared_ptr<Planet> ocean = std::make_shared<Planet>("Ocean", myEarth->getPosition(), earthRadius + 0.35f, oceanProgram);
	oceanProgram->setUniform("lightPosition", lightPosition);

	addPlanet(myEarth);
	addPlanet(ocean);
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
