#ifndef EMISSIVEPLANET_HPP
#define EMISSIVEPLANET_HPP

#include "Planet.hpp"

class EmissivePlanet : public Planet
{
private:
	float _emissivePower = 1.f;

public:

	inline void setEmissivePower(float emissivePower) { this->_emissivePower = emissivePower; }
	inline float getEmissivePower() const { return this->_emissivePower; }

	EmissivePlanet() {}
	EmissivePlanet(const std::string& name, const glm::vec3& position, const float radius, const float emissivePower, const Program& sphereProgram)
		: Planet(name, position, radius, sphereProgram), _emissivePower(emissivePower) {}

	virtual ~EmissivePlanet() {}
};


#endif /* EMISSIVEPLANET_HPP */
