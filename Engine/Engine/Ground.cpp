
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

void Ground::createPerlinGroundMesh(const int noiseWidth, const int noiseHeight, const float heightWeight)
{
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> texCoords;
	std::vector<glm::u32vec3> tris;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec3> colors;

	std::shared_ptr<Noiser> noiser = std::make_shared<Noiser>();
	float* noiseData = noiser->generatePerlinNoise2D(noiseWidth, noiseHeight);

	int topLeftX = static_cast<int>((noiseWidth - 1) * -0.5f);
	int topLeftZ = static_cast<int>((noiseHeight - 1) * 0.5f);
	int vertexIndex = 0;

	glm::vec3 grassColor = glm::vec3(0.f, 1.f, 0.f);
	glm::vec3 dirtColor = glm::vec3(0.73f, 0.34f, 0.f);

	vertices.reserve(noiseWidth * noiseHeight);
	texCoords.reserve(noiseWidth * noiseHeight);
	tris.reserve((noiseWidth - 1) * (noiseHeight - 1) * 2);
	colors.reserve(noiseWidth * noiseHeight);
	for (int y = 0; y < noiseHeight; ++y)
	{
		for (int x = 0; x < noiseWidth; ++x)
		{
			float noiseValue = noiseData[y * noiseWidth + x];

			glm::vec3 vertex = glm::vec3(topLeftX + x, noiseValue * heightWeight, topLeftZ - y);
			vertices.push_back(vertex);
			texCoords.push_back(glm::vec2(float(x) / float(noiseWidth), float(y) / float(noiseHeight)));

			if (x < noiseWidth - 1 && y < noiseHeight - 1)
			{
				tris.push_back(glm::u32vec3(vertexIndex, vertexIndex + noiseWidth + 1, vertexIndex + noiseWidth));
				tris.push_back(glm::u32vec3(vertexIndex + noiseWidth + 1, vertexIndex, vertexIndex + 1));
			}
			++vertexIndex;

			float colorWeight = glm::smoothstep(0.1f, 0.8f, noiseValue);
			glm::vec3 color = glm::mix(dirtColor, grassColor, colorWeight);
			colors.push_back(color);
		}
	}

	normals.resize(vertices.size(), {0,0,0});
	for (const glm::u32vec3& tri : tris)
	{
		glm::vec3 v1 = vertices[tri.y] - vertices[tri.x];
		glm::vec3 v2 = vertices[tri.z] - vertices[tri.x];
		glm::vec3 n = cross(v1, v2);
		normals[tri.x] += n;
		normals[tri.y] += n;
		normals[tri.z] += n;
	}
	for (glm::vec3& n : normals)
	{
		n = glm::normalize(n);
	}

	this->mesh.createMesh(vertices, normals, texCoords, tris, colors);
	this->mesh.createMeshGL();
	this->isCreated = true;

	delete[] noiseData;
}
