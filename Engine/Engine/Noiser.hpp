#ifndef NOISER_HPP
#define NOISER_HPP

#include <memory>

class Noiser
{
private:


public:

	unsigned char* generatePerlinNoise2D(int width, int height, float frequency, float amplitude, int octaves, float persistence, float lacunarity, int seed);
	
	Noiser() {}
	virtual ~Noiser() {}
};


#endif /* NOISER_HPP */
