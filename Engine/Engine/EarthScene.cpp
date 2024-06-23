
#include "EarthScene.hpp"

#include "QuadModel.hpp"

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

	std::shared_ptr<Program> groundProgram = std::make_shared<Program>("render.vert", "ground.frag");
	std::shared_ptr<QuadModel> ground = std::make_shared<QuadModel>();
	glm::vec3 lt = glm::vec3(-50, -1, -100);
	glm::vec3 rb = glm::vec3(50, -1, 20);
	ground->createQuad(lt, rb);
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
