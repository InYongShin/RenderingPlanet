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

	bool isCreated = false;
public:

	void createPlanet(const float radisu = 1.f);

	void setSphereProgram(const Program& program);

	void draw() const;
	
	Planet() {}
	Planet(const std::string& name, const float radius) : _name(name), _radius(radius)
	{
		createPlanet(radius); 
	}

	virtual ~Planet() {}
};


#endif /* PLANET_HPP */
