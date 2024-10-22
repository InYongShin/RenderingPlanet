
#include "Noiser.hpp"

#include "Framebuffer.hpp"
#include "Program.hpp"
#include "QuadModel.hpp"


// source: https://www.shadertoy.com/view/lsf3WH


float Noiser::hash(glm::vec2 p)
{
    int n = p.x * 3 + p.y * 113;

    // 1D hash by Hugo Elias
    n = (n << 13) ^ n;
    n = n * (n * n * 15731 + 789221) + 1376312589;
    return -1.f + 2.f * float( n & 0x0fffffff) / float(0x0fffffff);
}

float Noiser::noise(glm::vec2 p)
{
    glm::vec2 i = glm::floor(p);
    glm::vec2 f = glm::fract(p);

    // cubic interpolant
    glm::vec2 u = f * f * (glm::vec2(3.f) - glm::vec2(2.f) * f);

    return glm::mix( glm::mix( hash( i + glm::vec2(0,0) ), hash( i + glm::vec2(1,0) ), u.x), 
           glm::mix(           hash( i + glm::vec2(0,1) ), hash( i + glm::vec2(1,1) ), u.x), 
           u.y);
}

float Noiser::generatePerlinNoise(glm::vec2 p)
{
    float f = 0.f;

    p *= glm::vec2(8.f);
    glm::mat2 m = glm::mat2( 1.6f, 1.2f, 
                            -1.2f, 1.6f);

    f  = 0.5000 * noise(p); p = m * p;
    f += 0.2500 * noise(p); p = m * p;
    f += 0.1250 * noise(p); p = m * p;
    f += 0.0625 * noise(p); p = m * p;

    return 0.5 + 0.5 * f;
}

float* Noiser::generatePerlinNoise2D(const int width, const int height)
{
	float* data = new float[width * height];

	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			glm::vec2 p = glm::vec2(x, y) / glm::vec2(width, height);
			data[y * width + x] = generatePerlinNoise(p);
		}
	}

	return data;
}

unsigned char* Noiser::generatePerlinNoise2DGPU(int width, int height)
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
