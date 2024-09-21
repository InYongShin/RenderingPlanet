
#include "Noiser.hpp"

#include "Framebuffer.hpp"
#include "Program.hpp"
#include "QuadModel.hpp"

unsigned char* Noiser::generatePerlinNoise2D(int width, int height, float frequency, float amplitude, int octaves, float persistence, float lacunarity, int seed)
{
	Framebuffer framebuffer(1024, 1024, GL_UNSIGNED_BYTE, 3);
	framebuffer.use();
	
	std::shared_ptr<Program> perlinProgram = std::make_shared<Program>("texture.vert", "perlin.frag");
	perlinProgram->use();
	perlinProgram->setUniform("width", width);
	perlinProgram->setUniform("height", height);
	perlinProgram->setUniform("frequency", frequency);
	perlinProgram->setUniform("amplitude", amplitude);
	perlinProgram->setUniform("octaves", octaves);
	perlinProgram->setUniform("persistence", persistence);
	perlinProgram->setUniform("lacunarity", lacunarity);
	perlinProgram->setUniform("seed", seed);

	std::shared_ptr<QuadModel> quad = std::make_shared<QuadModel>();
	quad->createScreenQuad();
	quad->setProgram(perlinProgram);
	quad->draw();

	unsigned char* data = framebuffer.readPixels();
	framebuffer.unuse();

	return data;
}
