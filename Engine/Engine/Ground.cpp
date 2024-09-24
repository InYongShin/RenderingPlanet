
#include "Ground.hpp"

#include "Noiser.hpp"

void Ground::createGroundMesh(const glm::vec2& size)
{
	glm::vec3 ltPtn = glm::vec3(-size.x * .5f, 0.f, -size.y * .5f);
	glm::vec3 lbPtn = glm::vec3(-size.x * .5f, 0.f,  size.y * .5f);
	glm::vec3 rtPtn = glm::vec3( size.x * .5f, 0.f, -size.y * .5f);
	glm::vec3 rbPtn = glm::vec3( size.x * .5f, 0.f,  size.y * .5f);

	this->mesh.createQuad(ltPtn, rtPtn, lbPtn, rbPtn);
	this->mesh.createMeshGL();
	this->isCreated = true;
}

void Ground::createGroundMesh(const glm::vec2& size, const int noiseWidth, const int noiseHeight)
{
	std::shared_ptr<Noiser> noiser = std::make_shared<Noiser>();
	float* noiseData = noiser->generatePerlinNoise2D(noiseWidth, noiseHeight);

	// create the mesh using the noise data

}
