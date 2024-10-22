#ifndef NOISER_HPP
#define NOISER_HPP

#include "GLTools.hpp"

#include <memory>

class Noiser
{
private:
	float hash(glm::vec2 p);
	float noise(glm::vec2 p);
	float generatePerlinNoise(glm::vec2 p);

public:

	float* generatePerlinNoise2D(const int width, const int height);

	// TODO: Refactoring from unsigned char to float
	unsigned char* generatePerlinNoise2DGPU(int width, int height);
	
	Noiser() {}
	virtual ~Noiser() {}
};


#endif /* NOISER_HPP */
