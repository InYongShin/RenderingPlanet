
#include "EarthScene.hpp"

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
