#include "MySpaceScene.hpp"

#include "MyEarth.hpp"

#include "RenderManager.hpp"
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
	const glm::vec3& earthPosition = glm::vec3(0.0f);

	// Earth grond
	{
		std::unique_ptr<RenderPass> myEarthRenderPass = std::make_unique<RenderPass>();
		
		std::shared_ptr<Program> myEarthProgram = std::make_shared<Program>("myearth.vert", "myearth.frag");
		myEarthProgram->setUniform("lightPosition", lightPosition);
		myEarthRenderPass->setProgram(myEarthProgram);

		std::shared_ptr<MyEarth> myEarth = std::make_shared<MyEarth>("MyEarth", earthPosition, earthRadius, 100);
		myEarthRenderPass->addModel(myEarth->getSphere());

		RenderManager::getInstance()->addRenderPass(myEarthRenderPass);

		addPlanet(myEarth);
	}

	// Earth ocean
	{
		std::unique_ptr<RenderPass> oceanRenderPass = std::make_unique<RenderPass>();
	
		std::shared_ptr<Program> oceanProgram = std::make_shared<Program>("ocean.vert", "ocean.frag");
		oceanProgram->setUniform("lightPosition", lightPosition);
		oceanRenderPass->setProgram(oceanProgram);

		std::shared_ptr<Planet> ocean = std::make_shared<Planet>("Ocean", earthPosition, earthRadius + 0.35f);
		oceanRenderPass->addModel(ocean->getSphere());

		RenderManager::getInstance()->addRenderPass(oceanRenderPass);

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
