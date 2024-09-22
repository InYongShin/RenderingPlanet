
#include "EarthScene.hpp"

#include "QuadModel.hpp"
#include "Noiser.hpp"
#include "TextureManager.hpp"

EarthScene::EarthScene()
	: Scene()
{
}

EarthScene::EarthScene(const std::string& title)
	: Scene(title)
{
	initialize();
}

void EarthScene::initialize()
{
	setBackgroundColor(glm::vec4(0.31f, 0.73f, 0.87f, 1.0f));
	glm::vec3 lightPos = glm::vec3(-100.f, 30.f, -100.f);



	std::shared_ptr<SphereModel> sun = std::make_shared<SphereModel>();
	sun->createSphere(10.f);
	sun->setPosition(lightPos);
	sun->addTexture(TextureManager::getInstance()->loadTexture("../Textures/Sun.jpg"), "tex");
	sun->setProgram(std::make_shared<Program>("render.vert", "sun.frag"));

	addModel(sun);

	

	std::shared_ptr<Noiser> noiser = std::make_shared<Noiser>();
	unsigned char* heightData = noiser->generatePerlinNoise2D(1024, 1024, 0.1f, 0.5f, 8, 0.5f, 2.0f, 0);
	int heightTexID = TextureManager::getInstance()->setTexture(1024, 1024, GL_UNSIGNED_BYTE, 3, heightData);

	std::shared_ptr<Program> groundProgram = std::make_shared<Program>("ground.vert", "ground.frag");
	groundProgram->setUniform("lightPosition", lightPos);

	std::shared_ptr<QuadModel> ground = std::make_shared<QuadModel>();
	glm::vec3 lt = glm::vec3(-100, -30, -100);
	glm::vec3 rb = glm::vec3(100, -30, 100);
	ground->createQuad(lt, rb, 100);
	ground->addTexture(heightTexID, "heightMap");

	ground->setProgram(groundProgram);

	addModel(ground);

}

void EarthScene::update()
{

}

void EarthScene::addModel(const std::shared_ptr<Model>& model)
{
	if (model == nullptr)
	{
		std::cerr << "Model is nullptr" << std::endl;
		return;
	}

	this->models.push_back(model);
}

void EarthScene::drawContents() const /*override*/
{
	for (auto& model : this->models)
	{
		model->draw();
	}
}