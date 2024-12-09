
#include "EarthScene.hpp"

#include "Ground.hpp"
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
	sun->createSphere(10.f, 63, 65);
	sun->setPosition(lightPos);
	sun->addTexture(TextureManager::getInstance()->loadTexture("../Textures/Sun.jpg"), "tex");
	sun->setProgram(std::make_shared<Program>("render.vert", "sun.frag"));
	addModel(sun);

	std::shared_ptr<Program> groundProgram = std::make_shared<Program>("ground.vert", "ground.frag");
	groundProgram->setUniform("lightPosition", lightPos);

	std::shared_ptr<Ground> ground = std::make_shared<Ground>(glm::vec3(0.f, -30.f, 0.f), glm::vec3(0.f, 1.f, 0.f));
	ground->createPerlinGroundMesh(200, 200, 30.f);
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
