
#include "Noiser.hpp"


const std::shared_ptr<unsigned char> Noiser::generatePerlinNoise2D(int width, int height, float frequency, float amplitude, int octaves, float persistence, float lacunarity, int seed)
{
	std::shared_ptr<unsigned char> data = std::make_shared<unsigned char>(width * height);

}
