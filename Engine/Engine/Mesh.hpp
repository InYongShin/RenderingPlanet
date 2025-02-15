#ifndef MESH_HPP
#define MESH_HPP

#include "GLTools.hpp"

#include <vector>

class Mesh
{
private:
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> texCoords;
	std::vector<glm::u32vec3> tris;
	std::vector<glm::vec3> colors;

public:
	GLuint vao=0, vBuf=0, eBuf=0, tBuf=0, nBuf=0, cBuf=0;
	GLsizei nTris=0, nVerts=0;
	GLenum primitive=GL_TRIANGLES;

	void createMeshGL();

	void createMesh(const std::vector<glm::vec3>& vertices, const std::vector<glm::vec3>& normals, const std::vector<glm::vec2>& texCoords, const std::vector<glm::u32vec3>& tris);
	void createMesh(const std::vector<glm::vec3>& vertices, const std::vector<glm::vec3>& normals, const std::vector<glm::vec2>& texCoords, const std::vector<glm::u32vec3>& tris, const std::vector<glm::vec3>& colors);
	void createSphere(float radius, int slices, int stacks);
	void createSphere(float radius, int slices, int stacks, const float noiseWeight);
	void createSphere(float radius, int resolution);
	void createQuad(const glm::vec3& ltPtn, const glm::vec3& rtPtn, const glm::vec3& lbPtn, const glm::vec3& rbPtn);
	void createQuad(const glm::vec3& ltPtn, const glm::vec3& rtPtn, const glm::vec3& lbPtn, const glm::vec3& rbPtn, const int resolution);

	void clearMeshData();
	void clear();

	Mesh() {}
	virtual ~Mesh() { clear(); }
};

#endif /* MESH_HPP */
