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

public:
	GLuint vao=0, vBuf=0, eBuf=0, tBuf=0, nBuf=0;
	GLsizei nTris=0, nVerts=0;

	void createMeshGL();

	void createSphere(float radius, int slices, int stacks);
	void createQuad(const glm::vec3& ltPtn, const glm::vec3& rtPtn, const glm::vec3& lbPtn, const glm::vec3& rbPtn);

	void clearMeshData();
	void clear();

	Mesh() {}
	virtual ~Mesh() { clear(); }
};

#endif /* MESH_HPP */
