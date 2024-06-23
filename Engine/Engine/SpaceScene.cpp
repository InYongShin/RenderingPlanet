
#include "SpaceScene.hpp"
#include "Texture.hpp"
#include "EmissivePlanet.hpp"
#include "QuadModel.hpp"

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

void SpaceScene::initialize() /*override*/
{
	std::shared_ptr<Program> sunProgram = std::make_shared<Program>("render.vert", "texture.frag");
	int sunTexID = TextureManager::getInstance()->loadTexture("../Textures/Sun.jpg");
	std::shared_ptr<EmissivePlanet> sun = std::make_shared<EmissivePlanet>("Sun", glm::vec3(-12.f, 0.f, 0.f), 10.9f, 1.f, sunProgram, sunTexID, "tex");
	addPlanet(sun);

	std::shared_ptr<Program> mercuryProgram = std::make_shared<Program>("render.vert", "render.frag");
	int mercuryTexID = TextureManager::getInstance()->loadTexture("../Textures/Mercury.jpg");
	std::shared_ptr<Planet> mercury = std::make_shared<Planet>("Mercury", glm::vec3(-0.61f, 0.f, 0.f), 0.04f, mercuryProgram, mercuryTexID, "tex");
	mercuryProgram->setUniform("lightPosition", sun->getPosition());
	mercuryProgram->setUniform("lightPower", sun->getEmissivePower());
	addPlanet(mercury);

	std::shared_ptr<Program> venusProgram = std::make_shared<Program>("render.vert", "render.frag");
	int venusTexID = TextureManager::getInstance()->loadTexture("../Textures/Venus.jpg");
	std::shared_ptr<Planet> venus = std::make_shared<Planet>("Venus", glm::vec3(-0.28f, 0.f, 0.f), .09f, venusProgram, venusTexID, "tex");
	venusProgram->setUniform("lightPosition", sun->getPosition());
	venusProgram->setUniform("lightPower", sun->getEmissivePower());
	addPlanet(venus);
	
	std::shared_ptr<Program> earthProgram = std::make_shared<Program>("render.vert", "render.frag");
	int earthTexID = TextureManager::getInstance()->loadTexture("../Textures/Earth.jpg");
	std::shared_ptr<Planet> earth = std::make_shared<Planet>("Earth", glm::vec3(0.f, 0.f, 0.f), 0.1f, earthProgram, earthTexID, "tex");
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
	earthTextQuad->addTexture(4, "tex");
	earth->addModel(earthTextQuad);

	std::shared_ptr<Program> moonProgram = std::make_shared<Program>("render.vert", "render.frag");
	int moonTexID = TextureManager::getInstance()->loadTexture("../Textures/Moon.jpg");
	std::shared_ptr<Planet> moon = std::make_shared<Planet>("Moon", glm::vec3(.15f, 0.f, 0.f), 0.025f, moonProgram, moonTexID, "tex");
	moonProgram->setUniform("lightPosition", sun->getPosition());
	moonProgram->setUniform("lightPower", sun->getEmissivePower());
	addPlanet(moon);

	std::shared_ptr<Program> marsProgram = std::make_shared<Program>("render.vert", "render.frag");
	int marsTexID = TextureManager::getInstance()->loadTexture("../Textures/Mars.jpg");
	std::shared_ptr<Planet> mars = std::make_shared<Planet>("Mars", glm::vec3(0.52f, 0.f, 0.f), .05f, marsProgram, marsTexID, "tex");
	marsProgram->setUniform("lightPosition", sun->getPosition());
	marsProgram->setUniform("lightPower", sun->getEmissivePower());
	addPlanet(mars);

	std::shared_ptr<Program> jupiterProgram = std::make_shared<Program>("render.vert", "render.frag");
	int jupiterTexID = TextureManager::getInstance()->loadTexture("../Textures/Jupiter.jpg");
	std::shared_ptr<Planet> jupiter = std::make_shared<Planet>("Jupiter", glm::vec3(4.2f, 0.f, 0.f), 1.12f, jupiterProgram, jupiterTexID, "tex");
	jupiterProgram->setUniform("lightPosition", sun->getPosition());
	jupiterProgram->setUniform("lightPower", sun->getEmissivePower());
	addPlanet(jupiter);

	std::shared_ptr<Program> saturnProgram = std::make_shared<Program>("render.vert", "render.frag");
	int saturnTexID = TextureManager::getInstance()->loadTexture("../Textures/Saturn.jpg");
	std::shared_ptr<Planet> saturn = std::make_shared<Planet>("Saturn", glm::vec3(8.52f, 0.f, 0.f), 0.94f, saturnProgram, saturnTexID, "tex");
	saturnProgram->setUniform("lightPosition", sun->getPosition());
	saturnProgram->setUniform("lightPower", sun->getEmissivePower());
	addPlanet(saturn);

	std::shared_ptr<Program> uranusProgram = std::make_shared<Program>("render.vert", "render.frag");
	int uranusTexID = TextureManager::getInstance()->loadTexture("../Textures/Uranus.jpg");
	std::shared_ptr<Planet> uranus = std::make_shared<Planet>("Uranus", glm::vec3(18.21f, 0.f, 0.f), 0.4f, uranusProgram, uranusTexID, "tex");
	uranusProgram->setUniform("lightPosition", sun->getPosition());
	uranusProgram->setUniform("lightPower", sun->getEmissivePower());
	addPlanet(uranus);

	std::shared_ptr<Program> neptuneProgram = std::make_shared<Program>("render.vert", "render.frag");
	int neptuneTexID = TextureManager::getInstance()->loadTexture("../Textures/Neptune.jpg");
	std::shared_ptr<Planet> neptune = std::make_shared<Planet>("Neptune", glm::vec3(29.07f, 0.f, 0.f), 0.39f, neptuneProgram, neptuneTexID, "tex");
	neptuneProgram->setUniform("lightPosition", sun->getPosition());
	neptuneProgram->setUniform("lightPower", sun->getEmissivePower());
	addPlanet(neptune);
}

void SpaceScene::update() /*override*/
{
	
}
