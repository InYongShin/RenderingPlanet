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

	// Earth ground
	{
		std::unique_ptr<RenderPass> myEarthRenderPass = std::make_unique<RenderPass>();
		
		std::shared_ptr<Program> myEarthProgram = std::make_shared<Program>("myearth.vert", "myearth.frag");
		myEarthProgram->setUniform("lightPosition", lightPosition);

		std::shared_ptr<MyEarth> myEarth = std::make_shared<MyEarth>("MyEarth", earthPosition, earthRadius, 100);
		myEarth->getSphere()->setProgram(myEarthProgram);
		myEarthRenderPass->addModel(myEarth->getSphere());

		RenderManager::getInstance()->addRenderPass(myEarthRenderPass);

		addPlanet(myEarth);
	}

	// Earth ocean
	{
		std::unique_ptr<RenderPass> oceanRenderPass = std::make_unique<RenderPass>();
	
		std::shared_ptr<Program> oceanProgram = std::make_shared<Program>("ocean.vert", "ocean.frag");
		oceanProgram->setUniform("lightPosition", lightPosition);

		std::shared_ptr<Planet> ocean = std::make_shared<Planet>("Ocean", earthPosition, earthRadius + 0.35f);
		ocean->getSphere()->setProgram(oceanProgram);
		oceanRenderPass->addModel(ocean->getSphere());

		RenderManager::getInstance()->addRenderPass(oceanRenderPass);

		addPlanet(ocean);
	}

	// Cloud
	{
		float volumeScaleX=5.f;
		float volumeScaleY=5.f;
		float volumeScaleZ=5.f;

		float r1 = 1.0f;
		float r2 = 2.0f;

		int numOctaves = 8;
		float rayStep = 0.1f;
		int maxStep = 32;
		float lightStep = 0.1f;
		int maxLightStep = 6;
		float frequency = 0.15f;
		float H = -0.6f;
		float coverage = 0.15f;
		float absorption = 1.f;
		float lightAbsorptionToSun = 1.f;
		float g = 0.2f;

		std::unique_ptr<RenderPass> cloudRenderPass = std::make_unique<RenderPass>();

		Camera cam = SceneManager::getInstance()->getCamera();

		cloudProgram = std::make_shared<Program>("quad.vert", "cloud.frag");

		cloudProgram->setUniform("viewport", cam.getViewport());
		cloudProgram->setUniform("camPos", cam.getPosition());
		cloudProgram->setUniform("camDir", cam.getDirection());
		cloudProgram->setUniform("lookAt", cam.viewMat());
		cloudProgram->setUniform("proj", cam.projMat());
		cloudProgram->setUniform("lightPos", lightPosition);
		cloudProgram->setUniform("lightCol", glm::vec3(1.0f, 1.0f, 1.0f));
		cloudProgram->setUniform("boundsMin", -glm::vec3(volumeScaleX, volumeScaleY-5, volumeScaleZ));
		cloudProgram->setUniform("boundsMax", glm::vec3(volumeScaleX, volumeScaleY+5, volumeScaleZ));

		cloudProgram->setUniform("volumeRadius", earthRadius * 1.3f);
		cloudProgram->setUniform("volumeCenter", earthPosition);


		cloudProgram->setUniform("r1", r1);
		cloudProgram->setUniform("r2", r2);

		cloudProgram->setUniform("rayStep", rayStep);

		cloudProgram->setUniform("maxLightStep", maxLightStep);
		cloudProgram->setUniform("frequency", frequency);
		cloudProgram->setUniform("numOctaves", numOctaves);
		cloudProgram->setUniform("coverage", coverage);
		cloudProgram->setUniform("absorption", absorption);
		cloudProgram->setUniform("lightAbsorptionToSun", lightAbsorptionToSun);
		cloudProgram->setUniform("H", H);
		cloudProgram->setUniform("g", g);
		cloudProgram->setUniform("maxStep", maxStep);
		cloudProgram->setUniform("backColor", glm::vec4(.31, .73, .87, 1));

		std::shared_ptr<QuadModel> quad = std::make_shared<QuadModel>();
		quad->createScreenQuad();
		quad->setProgram(cloudProgram);
		cloudRenderPass->addModel(quad);

		int cloudWidth = 64, cloudHeight = 64, cloudDepth = 64;
		Noiser noiser;
		float* data = noiser.generateCloudNoise(cloudWidth, cloudHeight, cloudDepth);

		int texID = TextureManager::getInstance()->setTexture3D(cloudWidth, cloudHeight, cloudDepth, GL_FLOAT, 1, data);
		quad->addTexture(texID, "cloudTex");

		RenderManager::getInstance()->addRenderPass(cloudRenderPass);
	}
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
