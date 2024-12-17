#include "MySpaceScene.hpp"

#include "MyEarth.hpp"

#include "RenderPass.hpp"

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


	// Earth grond
	{
		std::shared_ptr<RenderPass> myEarthRenderPass = std::make_shared<RenderPass>();

		std::shared_ptr<Program> myEarthProgram = std::make_shared<Program>("myearth.vert", "myearth.frag");
		myEarthProgram->setUniform("lightPosition", lightPosition);
		myEarthRenderPass->setProgram(myEarthProgram);

		std::shared_ptr<MyEarth> myEarth = std::make_shared<MyEarth>("MyEarth", glm::vec3(0.0f), earthRadius, 100);
		myEarth->setRenderPass(myEarthRenderPass);

		addPlanet(myEarth);
	}

	// Earth ocean
	{
		std::shared_ptr<RenderPass> oceanRenderPass = std::make_shared<RenderPass>();
	
		std::shared_ptr<Program> oceanProgram = std::make_shared<Program>("ocean.vert", "ocean.frag");
		oceanProgram->setUniform("lightPosition", lightPosition);
		oceanRenderPass->setProgram(oceanProgram);
	
		std::shared_ptr<Planet> ocean = std::make_shared<Planet>("Ocean", glm::vec3(0.0f), earthRadius + 0.35f);
		ocean->setRenderPass(oceanRenderPass);

		addPlanet(ocean);
	}

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
