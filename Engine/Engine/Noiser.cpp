
#include "Noiser.hpp"

#include "Framebuffer.hpp"
#include "Program.hpp"
#include "QuadModel.hpp"

unsigned char* Noiser::generatePerlinNoise2D(int width, int height)
{
	Framebuffer framebuffer(width, height, GL_UNSIGNED_BYTE, 3);
	framebuffer.use();
	
	std::shared_ptr<Program> perlinProgram = std::make_shared<Program>("texture.vert", "perlin.frag");
	perlinProgram->use();

	std::shared_ptr<QuadModel> quad = std::make_shared<QuadModel>();
	quad->createScreenQuad();
	quad->setProgram(perlinProgram);
	quad->draw();

	unsigned char* data = framebuffer.readPixels();
	framebuffer.unuse();

	return data;
}
