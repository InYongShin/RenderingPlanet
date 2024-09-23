#ifndef EARTH_HPP
#define EARTH_HPP

#include "Planet.hpp"

#include <string>

class Earth : public Planet
{
private:

public:

	void update() override;

	Earth() {}
	Earth(const std::string& name, 
		  const glm::vec3& position, 
		  const float radius, 
		  const std::shared_ptr<Program>& sphereProgram, 
		  const int texID = -1, 
		  const std::string& shaderTexName = "", 
		  const glm::vec3& centerPosition = glm::vec3(0.f), 
		  const float orbitSpeed = 0.f)
		: Planet(name, position, radius, sphereProgram, texID, shaderTexName, centerPosition, orbitSpeed) {}

	virtual ~Earth() {};
};



#endif /* EARTH_HPP */