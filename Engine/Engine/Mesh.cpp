
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
			glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(glm::vec2) * this->nVerts, this->texCoords.data() );
		}
		glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, this->eBuf);
		glBufferSubData( GL_ELEMENT_ARRAY_BUFFER, 0, sizeof(glm::u32vec3) * this->nTris, tris.data()  );
	}
	else {
		if (this->vao) glDeleteVertexArrays(1, &this->vao);
		if (this->vBuf) glDeleteBuffers(1, &this->vBuf);
		if (this->nBuf) glDeleteBuffers(1, &this->nBuf);
		if (this->tBuf) glDeleteBuffers(1, &this->tBuf);
		if (this->eBuf) glDeleteBuffers(1, &this->eBuf);
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
