#ifndef MYEARTH_HPP
#define MYEARTH_HPP

#include "Planet.hpp"

class MyEarth : public Planet
{
private:

public:
	MyEarth() {}
	MyEarth(const std::string& name,
			const glm::vec3& position,
			const float radius,
			const int resolution,
			const std::shared_ptr<Program>& sphereProgram)
			: Planet(name, position, radius, resolution, sphereProgram) {}
	MyEarth(const std::string& name,
			const glm::vec3& position,
			const float radius,
			const std::shared_ptr<Program>& sphereProgram,
			const int noiseWidth,
			const int noiseHeight,
			const float noiseWeight)
			: Planet(name, position, radius, sphereProgram, noiseWidth, noiseHeight, noiseWeight) {}

	virtual ~MyEarth() {};
};

#endif /* MYEARTH_HPP */