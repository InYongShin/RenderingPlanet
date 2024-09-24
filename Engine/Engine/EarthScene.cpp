
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

	
	const int perlinWidth = 1024;
	const int perlinHeight = 1024;

	std::shared_ptr<Noiser> noiser = std::make_shared<Noiser>();
	float* noiseData = noiser->generatePerlinNoise2D(perlinWidth, perlinHeight);

	std::shared_ptr<Program> groundProgram = std::make_shared<Program>("ground.vert", "ground.frag");
	groundProgram->setUniform("lightPosition", lightPos);

	std::shared_ptr<QuadModel> ground = std::make_shared<QuadModel>();
	glm::vec3 lt = glm::vec3(-100, -30, -100);
	glm::vec3 rb = glm::vec3(100, -30, 100);
	ground->createQuad(lt, rb, 100);

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
