#ifndef PLANET_HPP
#define PLANET_HPP

#include "SphereModel.hpp"
#include "Program.hpp"

#include <string>

class Planet
{
private:
	std::string _name = "";
	float _radius = 0.f;

	std::shared_ptr<SphereModel> sphere = nullptr;

	std::vector<std::shared_ptr<Model>> models;

	bool isCreated = false;
public:

	void createPlanet(const float radius = 1.f, const glm::vec3& position = glm::vec3(0.f));

	void setSphereProgram(const Program& program);

	inline void setPosition(const glm::vec3& position) { this->sphere->setPosition(position); }
	inline glm::vec3 getPosition() const { return this->sphere->getPosition(); }

	inline float getRadius() const { return this->_radius; }

	void draw() const;
	
	void addModel(const std::shared_ptr<Model>& model);

	Planet() {}
	Planet(const std::string& name, const glm::vec3& position, const float radius, const Program& sphereProgram) 
		: _name(name), _radius(radius)
	{
		createPlanet(radius, position);
		setSphereProgram(sphereProgram);
	}

	virtual ~Planet() {}
};


#endif /* PLANET_HPP */
