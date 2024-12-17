
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

glm::vec3 Noiser::hash(const glm::vec3& p)
{
    glm::ivec3 n = glm::ivec3( p.x*127 + p.y*311 + p.z*74,
                               p.x*269 + p.y*183 + p.z*246,
                               p.x*113 + p.y*271 + p.z*124);

    // 1D hash by Hugo Elias
    n = (n << 13) ^ n;
    n = n * (n * n * 15731 + 789221) + 1376312589;
    return glm::vec3(-1.0f) + glm::vec3(2.0f) * glm::vec3( n & glm::ivec3(0x0fffffff))/float(0x0fffffff);
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

float Noiser::perlinFbm(const glm::vec3& x, int numOctaves, float H)
{
    float G = exp2(-H);
    float f = 1.0;
    float a = 1.0;
    float t = 0.0;
    for( int i=0; i<numOctaves; i++ )
    {
        t += a*generatePerlinNoise3D(f*x);
        f *= 2.0;
        a *= G;
    }
    return t;
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

// https://iquilezles.org/articles/gradientnoise/
float Noiser::generatePerlinNoise3D(glm::vec3 x)
{
    // grid
    glm::vec3 p = floor(x);
    glm::vec3 w = fract(x);

    // quintic interpolant
    glm::vec3 u = w*w*w*(w*(w*glm::vec3(6.0)-glm::vec3(15.0))+glm::vec3(10.0));

    // gradients
    glm::vec3 ga = hash( p+glm::vec3(0.0,0.0,0.0) );
    glm::vec3 gb = hash( p+glm::vec3(1.0,0.0,0.0) );
    glm::vec3 gc = hash( p+glm::vec3(0.0,1.0,0.0) );
    glm::vec3 gd = hash( p+glm::vec3(1.0,1.0,0.0) );
    glm::vec3 ge = hash( p+glm::vec3(0.0,0.0,1.0) );
    glm::vec3 gf = hash( p+glm::vec3(1.0,0.0,1.0) );
    glm::vec3 gg = hash( p+glm::vec3(0.0,1.0,1.0) );
    glm::vec3 gh = hash( p+glm::vec3(1.0,1.0,1.0) );

    // projections
    float va = glm::dot( ga, w-glm::vec3(0.0,0.0,0.0) );
    float vb = glm::dot( gb, w-glm::vec3(1.0,0.0,0.0) );
    float vc = glm::dot( gc, w-glm::vec3(0.0,1.0,0.0) );
    float vd = glm::dot( gd, w-glm::vec3(1.0,1.0,0.0) );
    float ve = glm::dot( ge, w-glm::vec3(0.0,0.0,1.0) );
    float vf = glm::dot( gf, w-glm::vec3(1.0,0.0,1.0) );
    float vg = glm::dot( gg, w-glm::vec3(0.0,1.0,1.0) );
    float vh = glm::dot( gh, w-glm::vec3(1.0,1.0,1.0) );

    // interpolation
    return va + 
           u.x*(vb-va) + 
           u.y*(vc-va) + 
           u.z*(ve-va) + 
           u.x*u.y*(va-vb-vc+vd) + 
           u.y*u.z*(va-vc-ve+vg) + 
           u.z*u.x*(va-vb-ve+vf) + 
           u.x*u.y*u.z*(-va+vb+vc-vd+ve-vf-vg+vh);
}

float Noiser::getPerlinNoise(const glm::vec3& x, const int numOctaves, const float H)
{
	return perlinFbm(x, numOctaves, H);
}

unsigned char* Noiser::generatePerlinNoise2DGPU(int width, int height)
{
	Framebuffer framebuffer(width, height, GL_UNSIGNED_BYTE, 3);
	framebuffer.use();
	
	std::shared_ptr<Program> perlinProgram = std::make_shared<Program>("texture.vert", "perlin.frag");
	perlinProgram->use();

	std::shared_ptr<QuadModel> quad = std::make_shared<QuadModel>();
	quad->createScreenQuad();
	// quad->setProgram(perlinProgram);
	quad->draw();

	unsigned char* data = framebuffer.readPixels();
	framebuffer.unuse();

	return data;
}
