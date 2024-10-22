
#include "GLTools.hpp"
#include "Mesh.hpp"

#include <iostream>

void Mesh::createMeshGL()
{
	if (this->tris.size() == this->nTris && this->vertices.size() == this->nVerts && this->vao>0 && this->eBuf>0)
	{
		std::cout << "Updating mesh.\n";
		glBindBuffer(GL_ARRAY_BUFFER, this->vBuf);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(glm::vec3) * this->nVerts, this->vertices.data());
		if (this->normals.size() > 0)
		{
			glBindBuffer(GL_ARRAY_BUFFER, this->nBuf);
			glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(glm::vec3) * this->nVerts, this->normals.data());
		}
		if (this->texCoords.size() > 0)
		{
			glBindBuffer(GL_ARRAY_BUFFER, this->tBuf);
			glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(glm::vec2) * this->nVerts, this->texCoords.data());
		}
		if (this->colors.size() > 0)
		{
			glBindBuffer(GL_ARRAY_BUFFER, this->cBuf);
			glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(glm::vec3) * this->nVerts, this->colors.data());
		}
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->eBuf);
		glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, sizeof(glm::u32vec3) * this->nTris, tris.data());
	}
	else {
		if (this->vao) glDeleteVertexArrays(1, &this->vao);
		if (this->vBuf) glDeleteBuffers(1, &this->vBuf);
		if (this->nBuf) glDeleteBuffers(1, &this->nBuf);
		if (this->tBuf) glDeleteBuffers(1, &this->tBuf);
		if (this->eBuf) glDeleteBuffers(1, &this->eBuf);
		if (this->cBuf) glDeleteBuffers(1, &this->cBuf);
		this->nTris  = GLsizei(tris.size());
		this->nVerts = GLsizei(this->vertices.size());

		// Generate and bind the this->vao
		glGenVertexArrays(1, &this->vao);
		glBindVertexArray(this->vao);

		// Generate and bind the VBO
		glGenBuffers(1, &this->vBuf);
		glBindBuffer(GL_ARRAY_BUFFER, this->vBuf);
		glBufferData(GL_ARRAY_BUFFER, this->nVerts * sizeof(glm::vec3), this->vertices.data(), GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
		glEnableVertexAttribArray(0);

		// Generate and bind the NBO
		if(this->normals.size() > 0)
		{
			glGenBuffers(1, &this->nBuf);
			glBindBuffer(GL_ARRAY_BUFFER, this->nBuf);
			glBufferData(GL_ARRAY_BUFFER, this->normals.size() * sizeof(glm::vec3), this->normals.data(), GL_STATIC_DRAW);
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
			glEnableVertexAttribArray(1);
		}

		// Generate and bind the TBO
		if (this->texCoords.size() > 0)
		{
			glGenBuffers(1, &this->tBuf);
			glBindBuffer(GL_ARRAY_BUFFER, this->tBuf);
			glBufferData(GL_ARRAY_BUFFER, this->texCoords.size() * sizeof(glm::vec2), this->texCoords.data(), GL_STATIC_DRAW);
			glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
			glEnableVertexAttribArray(2);
		}

		if(this->colors.size() > 0)
		{
			glGenBuffers(1, &this->cBuf);
			glBindBuffer(GL_ARRAY_BUFFER, this->cBuf);
			glBufferData(GL_ARRAY_BUFFER, this->colors.size() * sizeof(glm::vec3), this->colors.data(), GL_STATIC_DRAW);
			glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
			glEnableVertexAttribArray(3);
		}

		// Generate and bind the EBO
		glGenBuffers(1, &this->eBuf);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->eBuf);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->nTris * sizeof(glm::u32vec3), tris.data(), GL_STATIC_DRAW);

		// Unbind the this->vao
		glBindVertexArray(0);
	}
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 );
	glBindBuffer( GL_ARRAY_BUFFER, 0 );
}

void Mesh::createMesh(const std::vector<glm::vec3>& vertices, const std::vector<glm::vec3>& normals, const std::vector<glm::vec2>& texCoords, const std::vector<glm::u32vec3>& tris)
{
	this->vertices = vertices;
	this->normals = normals;
	this->texCoords = texCoords;
	this->tris = tris;
}

void Mesh::createMesh(const std::vector<glm::vec3>& vertices, const std::vector<glm::vec3>& normals, const std::vector<glm::vec2>& texCoords, const std::vector<glm::u32vec3>& tris, const std::vector<glm::vec3>& colors)
{
	this->vertices = vertices;
	this->normals = normals;
	this->texCoords = texCoords;
	this->tris = tris;
	this->colors = colors;
}

void Mesh::createSphere(float radius, int slices, int stacks)
{
	// Create sphere
	for (int i = 0; i <= stacks; i++)
	{
		float V = i / (float)stacks;
		float phi = V * glm::pi<float>();

		// Loop through the slices
		for (int j = 0; j <= slices; j++)
		{
			float U = j / (float)slices;
			float theta = U * (glm::pi<float>() * 2);
		
			// Calculate the vertex position
			float x = cos(theta) * sin(phi);
			float y = cos(phi);
			float z = sin(theta) * sin(phi);
		
			// Create the vertex
			glm::vec3 vertex = glm::vec3(x, y, z) * radius;
			this->vertices.push_back(vertex);
			this->normals.push_back(glm::normalize(vertex));
			this->texCoords.push_back(glm::vec2(U, V));
		}
	}
		
	// Calculate the indices
	for (int i = 0; i < slices * stacks + slices; i++)
	{
		tris.push_back(glm::u32vec3(i, i + slices + 1, i + slices));
		tris.push_back(glm::u32vec3(i + slices + 1, i, i + 1));
	}
}

void Mesh::createQuad(const glm::vec3& ltPtn, const glm::vec3& rtPtn, const glm::vec3& lbPtn, const glm::vec3& rbPtn)
{
	this->vertices.push_back(ltPtn);
	this->vertices.push_back(rtPtn);
	this->vertices.push_back(lbPtn);
	this->vertices.push_back(rbPtn);

	glm::vec3 normal = glm::normalize(glm::cross(rbPtn - ltPtn, rtPtn - ltPtn));
	this->normals.push_back(normal);
	this->normals.push_back(normal);
	this->normals.push_back(normal);
	this->normals.push_back(normal);

	this->texCoords.push_back(glm::vec2(0.f, 1.f));
	this->texCoords.push_back(glm::vec2(1.f, 1.f));
	this->texCoords.push_back(glm::vec2(0.f, 0.f));
	this->texCoords.push_back(glm::vec2(1.f, 0.f));

	this->tris.push_back(glm::u32vec3(0, 2, 1));
	this->tris.push_back(glm::u32vec3(1, 2, 3));
}

void Mesh::createQuad(const glm::vec3& ltPtn, const glm::vec3& rtPtn, const glm::vec3& lbPtn, const glm::vec3& rbPtn, const int resolution)
{
	glm::vec3 normal = glm::normalize(glm::cross(rbPtn - ltPtn, rtPtn - ltPtn));
	glm::vec3 horizontalStep = (rtPtn - ltPtn) / float(resolution);
	glm::vec3 verticalStep = (lbPtn - ltPtn) / float(resolution);

	for (int i = 0; i <= resolution; ++i)
	{
		for (int j = 0; j <= resolution; ++j)
		{
			glm::vec3 vertex = ltPtn + horizontalStep * float(j) + verticalStep * float(i);
			this->vertices.push_back(vertex);
			this->normals.push_back(normal);
			this->texCoords.push_back(glm::vec2(float(j) / float(resolution), float(i) / float(resolution)));
		}
	}

	for (int i = 0; i < resolution; ++i)
	{
		for (int j = 0; j < resolution; ++j)
		{
			int idx = i * (resolution + 1) + j;
			this->tris.push_back(glm::u32vec3(idx, idx + resolution + 1, idx + 1));
			this->tris.push_back(glm::u32vec3(idx + 1, idx + resolution + 1, idx + resolution + 2));
		}
	}
}

void Mesh::clearMeshData()
{
	this->vertices.clear();
	this->normals.clear();
	this->texCoords.clear();
	this->tris.clear();
}

void Mesh::clear()
{
	clearMeshData();
	if (this->vao  != 0) { glDeleteVertexArrays(1, &this->vao); this->vao = 0; }
	if (this->vBuf != 0) { glDeleteBuffers(1, &this->vBuf); this->vBuf = 0; }
	if (this->eBuf != 0) { glDeleteBuffers(1, &this->eBuf); this->eBuf = 0; }
	if (this->tBuf != 0) { glDeleteBuffers(1, &this->tBuf); this->tBuf = 0; }
	if (this->nBuf != 0) { glDeleteBuffers(1, &this->nBuf); this->nBuf = 0; }
}
