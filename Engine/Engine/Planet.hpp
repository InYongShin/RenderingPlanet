#ifndef PLANET_HPP
#define PLANET_HPP

#include "SphereModel.hpp"
#include "Program.hpp"
#include "Texture.hpp"

#include <string>

class Planet
{
private:
	std::string _name = "";
	float _radius = 0.f;

	std::shared_ptr<SphereModel> sphere = nullptr;

	std::vector<std::shared_ptr<Model>> models;

	bool isCreated = false;

protected:
	glm::vec3 centerPosition = glm::vec3(0.f);

public:

	// TODO: Texture를 어떻게 넘겨줄지. shader name 고민 필요
	void createPlanet(const float radius = 1.f, const glm::vec3& position = glm::vec3(0.f), const int texID = -1, const std::string& shaderTexName = "");

	void setSphereProgram(const std::shared_ptr<Program>& program);

	inline void setPosition(const glm::vec3& position) { this->sphere->setPosition(position); }
	inline glm::vec3 getPosition() const { return this->sphere->getPosition(); }

	inline float getRadius() const { return this->_radius; }

	void draw() const;
	
	virtual void update();

	void addModel(const std::shared_ptr<Model>& model);
	void addTexture(int id, const std::string& shaderName);

	Planet() {}
	Planet(const std::string& name, 
		   const glm::vec3& position, 
		   const float radius, 
		   const std::shared_ptr<Program>& sphereProgram, 
		   const int texID = -1, 
		   const std::string& shaderTexName = "",
		   const glm::vec3 centerPosition = glm::vec3(0.f)) 
		: _name(name), _radius(radius), centerPosition(centerPosition)
	{
		createPlanet(radius, position, texID, shaderTexName);
		setSphereProgram(sphereProgram);
	}

	virtual ~Planet() {}
};


#endif /* PLANET_HPP */
