#ifndef EMISSIVEPLANET_HPP
#define EMISSIVEPLANET_HPP

#include "Planet.hpp"

class EmissivePlanet : public Planet
{
private:

public:

	EmissivePlanet() {}
	EmissivePlanet(const std::string& name, float radius, const Program& sphereProgram)
		: Planet(name, radius, sphereProgram) {}

	virtual ~EmissivePlanet() {}
};


#endif /* EMISSIVEPLANET_HPP */
