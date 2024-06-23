#ifndef EARTHSCENE_HPP
#define EARTHSCENE_HPP

#include "Scene.hpp"

class EarthScene : public Scene
{
private:
	std::vector<std::shared_ptr<Model>> models;

public:
	void initialize() override;
	void update() override;

	void addModel(const std::shared_ptr<Model>& model);

	void drawContents() const override;

	EarthScene();
	EarthScene(const std::string& title);
	virtual ~EarthScene() {}
};


#endif /* EARTHSCENE_HPP */
