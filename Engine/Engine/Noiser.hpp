#ifndef NOISER_HPP
#define NOISER_HPP

#include "GLTools.hpp"

#include <memory>

class Noiser
{
private:
	float hash(glm::vec2 p);
	glm::vec3 hash(const glm::vec3& p);
	float noise(glm::vec2 p);

	float perlinFbm(const glm::vec3& x, int numOctaves, float H);

public:
	float generatePerlinNoise(glm::vec2 p);
	float* generatePerlinNoise2D(const int width, const int height);

	float generatePerlinNoise3D(glm::vec3 x);

	float getPerlinNoise(const glm::vec3& x, const int numOctaves, const float H);

	// TODO: Refactoring from unsigned char to float
	unsigned char* generatePerlinNoise2DGPU(int width, int height);
	
	Noiser() {}
	virtual ~Noiser() {}
};


#endif /* NOISER_HPP */
