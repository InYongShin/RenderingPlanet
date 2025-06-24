#ifndef NOISER_HPP
#define NOISER_HPP

#include "GLTools.hpp"

#include <memory>

class Noiser
{
private:
	float hash(const glm::vec2& p);
	glm::vec3 hash(const glm::vec3& p);
	float noise(const glm::vec2& p);

	float perlinFbm(const glm::vec3& x, int numOctaves, float H);

public:
	float generatePerlinNoise(glm::vec2 p);
	float* generatePerlinNoise2D(const int width, const int height);

	float generatePerlinNoise3D(const glm::vec3& x);

	float getPerlinNoise(const glm::vec3& x, const int numOctaves, const float H);

	// TODO: Refactoring from unsigned char to float
	unsigned char* generatePerlinNoise2DGPU(int width, int height);

	float remap(float x, float a, float b, float c, float d);
	float perlinFBM(const glm::vec3& p, const float numOctaves, float freq, const float H);
	float worley(const glm::vec3& p);
	float worleyFBM(const glm::vec3& p, const float freq);
	float sampleDensity(const glm::vec3& p, const float numOctaves, const float frequency, const float H, const float coverage);
	float* generateCloudNoise(const int width, const int height, const int depth);
	
	Noiser() {}
	virtual ~Noiser() {}
};


#endif /* NOISER_HPP */
