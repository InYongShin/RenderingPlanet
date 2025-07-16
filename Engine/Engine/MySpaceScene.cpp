#include "MySpaceScene.hpp"

#include "MyEarth.hpp"

#include "RenderManager.hpp"
#include "RenderPass.hpp"

#include "SceneManager.hpp"
#include "QuadModel.hpp"

#include "TextureManager.hpp"
#include "Noiser.hpp"

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

	glm::vec2 screenSize = SceneManager::getInstance()->getCamera().getViewport();
	std::unique_ptr<DepthRenderPass> screenDepthPass = std::make_unique<DepthRenderPass>(screenSize.x, screenSize.y);

	// Earth ground
	{
		std::unique_ptr<RenderPass> myEarthRenderPass = std::make_unique<RenderPass>();
		
		std::shared_ptr<Program> myEarthProgram = std::make_shared<Program>("Shader/myearth.vert", "Shader/myearth.frag");
		myEarthProgram->setUniform("lightPosition", lightPosition);

		std::shared_ptr<MyEarth> myEarth = std::make_shared<MyEarth>("MyEarth", earthPosition, earthRadius, 300);
		myEarth->getSphere()->setProgram(myEarthProgram);
		myEarthRenderPass->addModel(myEarth->getSphere());

		screenDepthPass->addModel(myEarth->getSphere());

		RenderManager::getInstance()->addRenderPass(myEarthRenderPass);

		addPlanet(myEarth);
	}

	// Earth ocean
	{
		std::unique_ptr<RenderPass> oceanRenderPass = std::make_unique<RenderPass>();
	
		std::shared_ptr<Program> oceanProgram = std::make_shared<Program>("Shader/ocean.vert", "Shader/ocean.frag");
		oceanProgram->setUniform("lightPosition", lightPosition);

		std::shared_ptr<Planet> ocean = std::make_shared<Planet>("Ocean", earthPosition, earthRadius + 0.35f);
		ocean->getSphere()->setProgram(oceanProgram);
		oceanRenderPass->addModel(ocean->getSphere());

		RenderManager::getInstance()->addRenderPass(oceanRenderPass);

		addPlanet(ocean);
	}

	// Cloud
	{
		float rayStep = 0.1f;
		int maxStep = 32;
		float lightStep = 0.1f;
		int maxLightStep = 6;
		float absorption = 1.f;
		float lightAbsorptionToSun = 1.f;

		std::unique_ptr<RenderPass> cloudRenderPass = std::make_unique<RenderPass>();

		Camera cam = SceneManager::getInstance()->getCamera();

		cloudProgram = std::make_shared<Program>("Shader/quad.vert", "Shader/cloud.frag");

		cloudProgram->setUniform("viewport", cam.getViewport());
		cloudProgram->setUniform("camPos", cam.getPosition());
		cloudProgram->setUniform("camDir", cam.getDirection());
		cloudProgram->setUniform("lookAt", cam.viewMat());
		cloudProgram->setUniform("proj", cam.projMat());
		cloudProgram->setUniform("lightPos", lightPosition);
		cloudProgram->setUniform("lightCol", glm::vec3(1.0f, 1.0f, 1.0f));

		cloudProgram->setUniform("volumeRadius", earthRadius * 1.2f);
		cloudProgram->setUniform("volumeCenter", earthPosition);

		cloudProgram->setUniform("rayStep", rayStep);

		cloudProgram->setUniform("maxLightStep", maxLightStep);
		cloudProgram->setUniform("absorption", absorption);
		cloudProgram->setUniform("lightAbsorptionToSun", lightAbsorptionToSun);
		cloudProgram->setUniform("maxStep", maxStep);
		cloudProgram->setUniform("backColor", glm::vec4(.31, .73, .87, 1));

		cloudProgram->setUniform("zNear", SceneManager::getInstance()->getCamera().getZNear());
		cloudProgram->setUniform("zFar", SceneManager::getInstance()->getCamera().getZFar());

		std::shared_ptr<QuadModel> quad = std::make_shared<QuadModel>();
		quad->createScreenQuad();
		quad->setProgram(cloudProgram);
		cloudRenderPass->addModel(quad);

		int cloudWidth = 64, cloudHeight = 64, cloudDepth = 64;
		Noiser noiser;
		float* data = noiser.generateCloudNoise(cloudWidth, cloudHeight, cloudDepth);

		int texID = TextureManager::getInstance()->setTexture3D(cloudWidth, cloudHeight, cloudDepth, GL_FLOAT, 1, data);
		quad->addTexture(texID, "cloudTex");

		quad->setUseDepthMap(true);

		RenderManager::getInstance()->addRenderPass(cloudRenderPass);
	}

	RenderManager::getInstance()->addDepthRenderPass(screenDepthPass);
}

void MySpaceScene::update() /*override*/
{
	for (auto& planet : this->planets)
	{
		planet->update();
	}

	if (cloudProgram && cloudProgram->isUsable())
	{
		Camera cam = SceneManager::getInstance()->getCamera();
		cloudProgram->setUniform("camPos", cam.getPosition());
		cloudProgram->setUniform("camDir", cam.getDirection());
		cloudProgram->setUniform("lookAt", cam.viewMat());
		cloudProgram->setUniform("viewport", cam.getViewport());
		cloudProgram->setUniform("proj", cam.projMat());
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
