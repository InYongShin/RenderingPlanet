
#include "SpaceScene.hpp"
#include "Texture.hpp"
#include "EmissivePlanet.hpp"
#include "QuadModel.hpp"
#include "Noiser.hpp"

#include "TextureManager.hpp"

SpaceScene::SpaceScene()
	: Scene()
{
}

SpaceScene::SpaceScene(const std::string& title)
	: Scene(title)
{
	initialize();
}

SpaceScene::~SpaceScene()
{
	this->planets.clear();
}

void SpaceScene::initialize() /*override*/
{
	setBackgroundColor(glm::vec4(0.f, 0.f, 0.f, 1.f));



	std::shared_ptr<Program> sunProgram = std::make_shared<Program>("render.vert", "texture.frag");
	int sunTexID = TextureManager::getInstance()->loadTexture("../Textures/Sun.jpg");
	std::shared_ptr<EmissivePlanet> sun = std::make_shared<EmissivePlanet>("Sun", glm::vec3(-6000.f, 0.f, 0.f), 1090.f, 1.f, sunProgram, sunTexID, "tex");
	addPlanet(sun);



	std::shared_ptr<Program> mercuryProgram = std::make_shared<Program>("render.vert", "render.frag");
	int mercuryTexID = TextureManager::getInstance()->loadTexture("../Textures/Mercury.jpg");
	std::shared_ptr<Planet> mercury = std::make_shared<Planet>("Mercury", glm::vec3(-61.0f, 0.f, 0.f), 4.0f, mercuryProgram, mercuryTexID, "tex");
	mercuryProgram->setUniform("lightPosition", sun->getPosition());
	mercuryProgram->setUniform("lightPower", sun->getEmissivePower());
	addPlanet(mercury);



	std::shared_ptr<Program> venusProgram = std::make_shared<Program>("render.vert", "render.frag");
	int venusTexID = TextureManager::getInstance()->loadTexture("../Textures/Venus.jpg");
	std::shared_ptr<Planet> venus = std::make_shared<Planet>("Venus", glm::vec3(-28.f, 0.f, 0.f), 9.f, venusProgram, venusTexID, "tex");
	venusProgram->setUniform("lightPosition", sun->getPosition());
	venusProgram->setUniform("lightPower", sun->getEmissivePower());
	addPlanet(venus);
	

	std::shared_ptr<Noiser> noiser = std::make_shared<Noiser>();
	unsigned char* noiseTextureData = noiser->generatePerlinNoise2D(1024, 1024, 0.1f, 0.5f, 8, 0.5f, 2.0f, 0);
	int earthHeightTexID = TextureManager::getInstance()->setTexture(1024, 1024, GL_UNSIGNED_BYTE, 3, noiseTextureData);

	std::shared_ptr<Program> earthProgram = std::make_shared<Program>("earth.vert", "earth.frag");
	int earthTexID = TextureManager::getInstance()->loadTexture("../Textures/Earth.jpg");

	std::shared_ptr<Planet> earth = std::make_shared<Planet>("Earth", glm::vec3(0.f, 0.f, 0.f), 10.f, earthProgram, earthTexID, "tex");
	earth->addTexture(earthHeightTexID, "heightMap");
	earthProgram->setUniform("lightPosition", sun->getPosition());
	earthProgram->setUniform("lightPower", sun->getEmissivePower());
	addPlanet(earth);

	std::shared_ptr<Program> earthTextProgram = std::make_shared<Program>("render.vert", "texture.frag");
	int earthTextTexID = TextureManager::getInstance()->loadTexture("../Textures/Earth Text.png");
	std::shared_ptr<QuadModel> earthTextQuad = std::make_shared<QuadModel>();
	glm::vec3 lt = glm::vec3(earth->getPosition() + glm::vec3(-earth->getRadius(), earth->getRadius() * 2.2f, 0.f));
	glm::vec3 rb = glm::vec3(earth->getPosition() + glm::vec3( earth->getRadius(), earth->getRadius() * 1.2f, 0.f));
	earthTextQuad->createQuad(lt, rb);
	earthTextQuad->setProgram(earthTextProgram);
	earthTextQuad->addTexture(earthTextTexID, "tex");
	earth->addModel(earthTextQuad);



	std::shared_ptr<Program> moonProgram = std::make_shared<Program>("render.vert", "render.frag");
	int moonTexID = TextureManager::getInstance()->loadTexture("../Textures/Moon.jpg");
	std::shared_ptr<Planet> moon = std::make_shared<Planet>("Moon", glm::vec3(15.f, 0.f, 0.f), 2.5f, moonProgram, moonTexID, "tex");
	moonProgram->setUniform("lightPosition", sun->getPosition());
	moonProgram->setUniform("lightPower", sun->getEmissivePower());
	addPlanet(moon);



	std::shared_ptr<Program> marsProgram = std::make_shared<Program>("render.vert", "render.frag");
	int marsTexID = TextureManager::getInstance()->loadTexture("../Textures/Mars.jpg");
	std::shared_ptr<Planet> mars = std::make_shared<Planet>("Mars", glm::vec3(52.f, 0.f, 0.f), 5.f, marsProgram, marsTexID, "tex");
	marsProgram->setUniform("lightPosition", sun->getPosition());
	marsProgram->setUniform("lightPower", sun->getEmissivePower());
	addPlanet(mars);



	std::shared_ptr<Program> jupiterProgram = std::make_shared<Program>("render.vert", "render.frag");
	int jupiterTexID = TextureManager::getInstance()->loadTexture("../Textures/Jupiter.jpg");
	std::shared_ptr<Planet> jupiter = std::make_shared<Planet>("Jupiter", glm::vec3(420.f, 0.f, 0.f), 112.f, jupiterProgram, jupiterTexID, "tex");
	jupiterProgram->setUniform("lightPosition", sun->getPosition());
	jupiterProgram->setUniform("lightPower", sun->getEmissivePower());
	addPlanet(jupiter);



	std::shared_ptr<Program> saturnProgram = std::make_shared<Program>("render.vert", "render.frag");
	int saturnTexID = TextureManager::getInstance()->loadTexture("../Textures/Saturn.jpg");
	std::shared_ptr<Planet> saturn = std::make_shared<Planet>("Saturn", glm::vec3(852.f, 0.f, 0.f), 94.f, saturnProgram, saturnTexID, "tex");
	saturnProgram->setUniform("lightPosition", sun->getPosition());
	saturnProgram->setUniform("lightPower", sun->getEmissivePower());
	addPlanet(saturn);



	std::shared_ptr<Program> uranusProgram = std::make_shared<Program>("render.vert", "render.frag");
	int uranusTexID = TextureManager::getInstance()->loadTexture("../Textures/Uranus.jpg");
	std::shared_ptr<Planet> uranus = std::make_shared<Planet>("Uranus", glm::vec3(1821.f, 0.f, 0.f), 40.f, uranusProgram, uranusTexID, "tex");
	uranusProgram->setUniform("lightPosition", sun->getPosition());
	uranusProgram->setUniform("lightPower", sun->getEmissivePower());
	addPlanet(uranus);



	std::shared_ptr<Program> neptuneProgram = std::make_shared<Program>("render.vert", "render.frag");
	int neptuneTexID = TextureManager::getInstance()->loadTexture("../Textures/Neptune.jpg");
	std::shared_ptr<Planet> neptune = std::make_shared<Planet>("Neptune", glm::vec3(2907.f, 0.f, 0.f), 39.f, neptuneProgram, neptuneTexID, "tex");
	neptuneProgram->setUniform("lightPosition", sun->getPosition());
	neptuneProgram->setUniform("lightPower", sun->getEmissivePower());
	addPlanet(neptune);
}

void SpaceScene::update() /*override*/
{
	
}

void SpaceScene::addPlanet(const std::shared_ptr<Planet>& planet)
{
	if (planet == nullptr)
	{
		std::cerr << "Planet is nullptr" << std::endl;
		return;
	}

	this->planets.push_back(planet);
}

void SpaceScene::drawContents() const /*override*/
{
	for (auto& planet : this->planets)
	{
		planet->draw();
	}
}
