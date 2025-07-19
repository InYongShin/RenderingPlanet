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

	SceneManager::getInstance()->getCamera().setPosition(glm::vec3(0.0f, 0.0f, 40.0f));

	Camera cam = SceneManager::getInstance()->getCamera();

	const glm::vec3& lightPosition = glm::vec3(500.f, 500.f, 500.f);
	const float earthRadius = 20.0f;
	const glm::vec3& earthPosition = glm::vec3(0.0f);

	glm::vec2 screenSize = cam.getViewport();
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

	// Ocean
	{
		std::unique_ptr<RenderPass> oceanRenderPass = std::make_unique<RenderPass>();

		this->oceanProgram = std::make_shared<Program>("Shader/quad.vert", "Shader/ocean.frag");

		this->oceanProgram->setUniform("viewport", cam.getViewport());
		this->oceanProgram->setUniform("camPos", cam.getPosition());
		this->oceanProgram->setUniform("lookAt", cam.viewMat());
		this->oceanProgram->setUniform("proj", cam.projMat());

		this->oceanProgram->setUniform("lightPosition", lightPosition);
		this->oceanProgram->setUniform("smoothness", 0.97f);
		this->oceanProgram->setUniform("waveScale", 1.0f);
		this->oceanProgram->setUniform("waveStrength", 10.0f);

		float time = static_cast<float>(glfwGetTime());
		this->oceanProgram->setUniform("time", time);

		this->oceanProgram->setUniform("oceanRadius", earthRadius);
		this->oceanProgram->setUniform("oceanCenter", earthPosition);
		this->oceanProgram->setUniform("colA", glm::vec3(76, 144, 241) / glm::vec3(255.0f));
		this->oceanProgram->setUniform("colB", glm::vec3(12, 75, 165) / glm::vec3(255.0f));
		this->oceanProgram->setUniform("depthMultiplier", 3.0f);
		this->oceanProgram->setUniform("alphaMultiplier", 30.0f);

		this->oceanProgram->setUniform("zNear", SceneManager::getInstance()->getCamera().getZNear());
		this->oceanProgram->setUniform("zFar", SceneManager::getInstance()->getCamera().getZFar());

		std::shared_ptr<QuadModel> quad = std::make_shared<QuadModel>();
		quad->createScreenQuad();
		quad->setProgram(this->oceanProgram);
		quad->setUseDepthMap(true);
		oceanRenderPass->addModel(quad);
		oceanRenderPass->offDepthTest();

		RenderManager::getInstance()->addRenderPass(oceanRenderPass);
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

		this->cloudProgram = std::make_shared<Program>("Shader/quad.vert", "Shader/cloud.frag");

		this->cloudProgram->setUniform("viewport", cam.getViewport());
		this->cloudProgram->setUniform("camPos", cam.getPosition());
		this->cloudProgram->setUniform("lookAt", cam.viewMat());
		this->cloudProgram->setUniform("proj", cam.projMat());
		this->cloudProgram->setUniform("lightPos", lightPosition);
		this->cloudProgram->setUniform("lightCol", glm::vec3(1.0f, 1.0f, 1.0f));

		this->cloudProgram->setUniform("volumeRadius", earthRadius * 1.2f);
		this->cloudProgram->setUniform("volumeCenter", earthPosition);

		this->cloudProgram->setUniform("rayStep", rayStep);

		this->cloudProgram->setUniform("maxLightStep", maxLightStep);
		this->cloudProgram->setUniform("absorption", absorption);
		this->cloudProgram->setUniform("lightAbsorptionToSun", lightAbsorptionToSun);
		this->cloudProgram->setUniform("maxStep", maxStep);

		this->cloudProgram->setUniform("zNear", SceneManager::getInstance()->getCamera().getZNear());
		this->cloudProgram->setUniform("zFar", SceneManager::getInstance()->getCamera().getZFar());

		std::shared_ptr<QuadModel> quad = std::make_shared<QuadModel>();
		quad->createScreenQuad();
		quad->setProgram(this->cloudProgram);
		cloudRenderPass->addModel(quad);
		cloudRenderPass->offDepthTest();

		int cloudWidth = 64, cloudHeight = 64, cloudDepth = 64;
		Noiser noiser;
		float* data = noiser.generateCloudNoise(cloudWidth, cloudHeight, cloudDepth);

		int texID = TextureManager::getInstance()->setTexture3D(cloudWidth, cloudHeight, cloudDepth, GL_FLOAT, 1, data);
		quad->addTexture(texID, "cloudTex");

		quad->setUseDepthMap(true);

		RenderManager::getInstance()->addRenderPass(cloudRenderPass);
	}

	{
		std::unique_ptr<RenderPass> sunRenderPass = std::make_unique<RenderPass>();

		std::shared_ptr<Program> sunProgram = std::make_shared<Program>("Shader/render.vert", "Shader/sun.frag");
		int sunTexID = TextureManager::getInstance()->loadTexture("../Textures/Sun.jpg");
		std::shared_ptr<Planet> sun = std::make_shared<Planet>("Sun", lightPosition, 500.0f, sunProgram, sunTexID, "tex");
		sun->getSphere()->setProgram(sunProgram);

		sunRenderPass->addModel(sun->getSphere());

		RenderManager::getInstance()->addRenderPass(sunRenderPass);

		addPlanet(sun);
	}

	RenderManager::getInstance()->addDepthRenderPass(screenDepthPass);
}

void MySpaceScene::update() /*override*/
{
	for (auto& planet : this->planets)
	{
		planet->update();
	}

	Camera cam = SceneManager::getInstance()->getCamera();
	if (this->cloudProgram && this->cloudProgram->isUsable())
	{
		this->cloudProgram->use();
		this->cloudProgram->setUniform("camPos", cam.getPosition());
		this->cloudProgram->setUniform("lookAt", cam.viewMat());
		this->cloudProgram->setUniform("viewport", cam.getViewport());
		this->cloudProgram->setUniform("proj", cam.projMat());
	}

	if (this->oceanProgram && this->oceanProgram->isUsable())
	{
		this->oceanProgram->use();
		this->oceanProgram->setUniform("viewport", cam.getViewport());
		this->oceanProgram->setUniform("camPos", cam.getPosition());
		this->oceanProgram->setUniform("lookAt", cam.viewMat());
		this->oceanProgram->setUniform("proj", cam.projMat());

		float time = static_cast<float>(glfwGetTime());
		this->oceanProgram->setUniform("time", time);
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
