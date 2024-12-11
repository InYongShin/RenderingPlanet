
#include "GLTools.hpp"
#include "Mesh.hpp"
#include "Noiser.hpp"

#include <iostream>
#include <array>

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
		this->tris.push_back(glm::u32vec3(i, i + slices + 1, i + slices));
		this->tris.push_back(glm::u32vec3(i + slices + 1, i, i + 1));
	}
}

void Mesh::createSphere(float radius, int slices, int stacks, const int noiseWidth, const int noiseHeight, const float noiseWeight)
{
	std::vector<glm::vec3> newVertices;
	std::vector<glm::u32vec3> newTris;
	std::vector<glm::vec2> newTexCoords;
	std::vector<glm::vec3> newColors;

	// Create initial icosahedron vertices
	float t = (1.0f + sqrt(5.0f)) * 0.5f;

	newVertices.reserve(12);

	newVertices.push_back(normalize(glm::vec3(-1,  t,  0)) * radius);
	newVertices.push_back(normalize(glm::vec3( 1,  t,  0)) * radius);
	newVertices.push_back(normalize(glm::vec3(-1, -t,  0)) * radius);
	newVertices.push_back(normalize(glm::vec3( 1, -t,  0)) * radius);

	newVertices.push_back(normalize(glm::vec3( 0, -1,  t)) * radius);
	newVertices.push_back(normalize(glm::vec3( 0,  1,  t)) * radius);
	newVertices.push_back(normalize(glm::vec3( 0, -1, -t)) * radius);
	newVertices.push_back(normalize(glm::vec3( 0,  1, -t)) * radius);

	newVertices.push_back(normalize(glm::vec3( t,  0, -1)) * radius);
	newVertices.push_back(normalize(glm::vec3( t,  0,  1)) * radius);
	newVertices.push_back(normalize(glm::vec3(-t,  0, -1)) * radius);
	newVertices.push_back(normalize(glm::vec3(-t,  0,  1)) * radius);

	// Create initial icosahedron faces

	newTris.reserve(20);

	newTris.push_back(glm::u32vec3(0, 11, 5));
	newTris.push_back(glm::u32vec3(0, 5, 1));
	newTris.push_back(glm::u32vec3(0, 1, 7));
	newTris.push_back(glm::u32vec3(0, 7, 10));
	newTris.push_back(glm::u32vec3(0, 10, 11));

	newTris.push_back(glm::u32vec3(1, 5, 9));
	newTris.push_back(glm::u32vec3(5, 11, 4));
	newTris.push_back(glm::u32vec3(11, 10, 2));
	newTris.push_back(glm::u32vec3(10, 7, 6));
	newTris.push_back(glm::u32vec3(7, 1, 8));

	newTris.push_back(glm::u32vec3(3, 9, 4));
	newTris.push_back(glm::u32vec3(3, 4, 2));
	newTris.push_back(glm::u32vec3(3, 2, 6));
	newTris.push_back(glm::u32vec3(3, 6, 8));
	newTris.push_back(glm::u32vec3(3, 8, 9));

	newTris.push_back(glm::u32vec3(4, 9, 5));
	newTris.push_back(glm::u32vec3(2, 4, 11));
	newTris.push_back(glm::u32vec3(6, 2, 10));
	newTris.push_back(glm::u32vec3(8, 6, 7));
	newTris.push_back(glm::u32vec3(9, 8, 1));

	// Subdivide triangles

	const int divCount = 7;
	newVertices.reserve(newVertices.size() + divCount * (newTris.size() * 3));
	for (int i = 0; i < divCount; ++i) {
		std::vector<glm::u32vec3> newTrisTemp;
		newTrisTemp.reserve(newTris.size() * 4);
		for (const auto& tri : newTris) {
			glm::vec3 v1 = normalize((newVertices[tri.x] + newVertices[tri.y]) * 0.5f) * radius;
			glm::vec3 v2 = normalize((newVertices[tri.y] + newVertices[tri.z]) * 0.5f) * radius;
			glm::vec3 v3 = normalize((newVertices[tri.z] + newVertices[tri.x]) * 0.5f) * radius;

			newVertices.push_back(v1);
			newVertices.push_back(v2);
			newVertices.push_back(v3);

			size_t i1 = newVertices.size() - 3;
			size_t i2 = newVertices.size() - 2;
			size_t i3 = newVertices.size() - 1;

			newTrisTemp.push_back(glm::u32vec3(tri.x, i1, i3));
			newTrisTemp.push_back(glm::u32vec3(tri.y, i2, i1));
			newTrisTemp.push_back(glm::u32vec3(tri.z, i3, i2));
			newTrisTemp.push_back(glm::u32vec3(i1, i2, i3));
		}
		newTris = newTrisTemp;
	}

	// Calculate texture coordinates and colors
	std::shared_ptr<Noiser> noiser = std::make_shared<Noiser>();
	glm::vec3 grassColor = glm::vec3(0.f, 1.f, 0.f);
	glm::vec3 dirtColor = glm::vec3(0.73f, 0.34f, 0.f);

	newTexCoords.reserve(newVertices.size());
	newColors.reserve(newVertices.size());
	for (auto& vertex : newVertices) {
		float u = 0.5f - atan2(vertex.z, vertex.x) / (2 * glm::pi<float>());
		float v = 0.5f + atan2(vertex.y, glm::length(glm::vec2(vertex.x, vertex.z))) / glm::pi<float>();
		newTexCoords.push_back(glm::vec2(u, v));

		// float noiseVal = noiser->generatePerlinNoise(glm::vec2(u, v));
		float noiseVal = noiser->generatePerlinNoise3D(vertex);
		glm::vec3 col = glm::mix(dirtColor, grassColor, glm::smoothstep(0.1f, 0.8f, noiseVal));
		newColors.push_back(col);

		glm::vec3 dir = glm::normalize(vertex);
		vertex += dir * noiseVal * noiseWeight;
	}

	this->vertices = newVertices;
	this->tris = newTris;
	this->texCoords = newTexCoords;
	this->colors = newColors;
	
	// Calculate the normals
	this->normals.resize(this->vertices.size(), {0,0,0});
	for (const glm::u32vec3& tri : this->tris)
	{
		glm::vec3 v1 = this->vertices[tri.y] - this->vertices[tri.x];
		glm::vec3 v2 = this->vertices[tri.z] - this->vertices[tri.x];
		glm::vec3 n = cross(v1, v2);
		this->normals[tri.x] += n;
		this->normals[tri.y] += n;
		this->normals[tri.z] += n;
	}
	for (glm::vec3& n : this->normals)
	{
		n = glm::normalize(n);
	}
}

// https://github.com/SebLague/Solar-System/blob/0c60882be69b8e96d6660c28405b9d19caee76d5/Assets/Scripts/Celestial/SphereMesh.cs
void Mesh::createSphere(float radius, int resolution)
{
	struct Edge {
		std::vector<int> vertexIndices;

		Edge() {}
		Edge(const std::vector<int>& indices) : vertexIndices(indices) {}
	};

	auto _slerp = [](const glm::vec3& start, const glm::vec3& end, float t) -> glm::vec3 {
		// Implement the Slerp function (Spherical Linear Interpolation)
		float dot = start.x * end.x + start.y * end.y + start.z * end.z;
		dot = glm::clamp(dot, -1.0f, 1.0f);  // Clamp to the range [ -1, 1 ]

		float theta = acos(dot) * t;
		glm::vec3 relativeVec = end - start * dot;
		relativeVec = relativeVec * (1.0f / sqrt(relativeVec.x * relativeVec.x + relativeVec.y * relativeVec.y + relativeVec.z * relativeVec.z));  // Normalize

		return (start * cos(theta)) + (relativeVec * sin(theta));
	};

	// Indices of the vertex pairs that make up each of the initial 12 edges
	std::array<int, 24> vertexPairs = { 0, 1, 0, 2, 0, 3, 0, 4, 1, 2, 2, 3, 
										3, 4, 4, 1, 5, 1, 5, 2, 5, 3, 5, 4 };
	// Indices of the edge triplets that make up the initial 8 faces
	std::array<int, 24> edgeTriplets = { 0, 1, 4, 1,  2, 5,  2,  3, 6,  3, 0, 7, 
										 8, 9, 4, 9, 10, 5, 10, 11, 6, 11, 8, 7 };
	// The six initial vertices
	std::array<glm::vec3, 6> baseVertices = { glm::vec3( 0.0f,  1.0f,  0.0f),
											  glm::vec3(-1.0f,  0.0f,  0.0f),
											  glm::vec3( 0.0f,  0.0f, -1.0f),
											  glm::vec3( 1.0f,  0.0f,  0.0f),
											  glm::vec3( 0.0f,  0.0f,  1.0f),
											  glm::vec3( 0.0f, -1.0f,  0.0f) };

	int numDivisions = resolution;
	int numVertsPerFace = ((numDivisions + 3) * (numDivisions + 3) - (numDivisions + 3)) / 2;
	int numVerts = numVertsPerFace * 8 - (numDivisions + 2) * 12 + 6;
	int numTrisPerFace = (numDivisions + 1) * (numDivisions + 1);

	auto _createFace = [&](const Edge& sideA, const Edge& sideB, const Edge& bottom, bool reverse) -> void {
		int numPointsInEdge = sideA.vertexIndices.size();
		std::vector<int> vertexMap;
		vertexMap.reserve(numVertsPerFace);
		vertexMap.push_back(sideA.vertexIndices[0]);

		for (int i = 1; i < numPointsInEdge - 1; i++) 
		{
			// Side A vertex
			vertexMap.push_back(sideA.vertexIndices[i]);

			// Add vertices between sideA and sideB
			glm::vec3 sideAVertex = this->vertices[sideA.vertexIndices[i]];
			glm::vec3 sideBVertex = this->vertices[sideB.vertexIndices[i]];
			int numInnerPoints = i - 1;
			for (int j = 0; j < numInnerPoints; j++) {
				float t = (j + 1.0f) / (numInnerPoints + 1.0f);
				vertexMap.push_back((int)this->vertices.size());
				this->vertices.push_back(_slerp(sideAVertex, sideBVertex, t));
			}

			// Side B vertex
			vertexMap.push_back(sideB.vertexIndices[i]);
		}

		// Add bottom edge vertices
		for (int i = 0; i < numPointsInEdge; i++) 
		{
			vertexMap.push_back(bottom.vertexIndices[i]);
		}

		// Triangulate
		int numRows = numDivisions + 1;
		for (int row = 0; row < numRows; row++) 
		{
			// vertices down left edge follow quadratic sequence: 0, 1, 3, 6, 10, 15...
			// the nth term can be calculated with: (n^2 - n)/2
			int topVertex = ((row + 1) * (row + 1) - row - 1) / 2;
			int bottomVertex = ((row + 2) * (row + 2) - row - 2) / 2;

			int numTrianglesInRow = 1 + 2 * row;
			for (int column = 0; column < numTrianglesInRow; column++) 
			{
				int v0, v1, v2;

				if (column % 2 == 0) {
					v0 = topVertex;
					v1 = bottomVertex + 1;
					v2 = bottomVertex;
					topVertex++;
					bottomVertex++;
				} else {
					v0 = topVertex;
					v1 = bottomVertex;
					v2 = topVertex - 1;
				}

				this->tris.push_back(glm::u32vec3(
					vertexMap[v0],
					vertexMap[reverse ? v2 : v1],
					vertexMap[reverse ? v1 : v2]
				));
			}
		}
	};

	this->vertices.reserve(numVerts);
	this->tris.reserve(numTrisPerFace * 8);

	this->vertices.insert(this->vertices.end(), std::begin(baseVertices), std::end(baseVertices));

	// Create 12 edges, with n vertices added along them (n = numDivisions)
	std::vector<Edge> edges(12);
	for (size_t i = 0; i < vertexPairs.size(); i += 2)
	{
		glm::vec3 startVertex = this->vertices[vertexPairs[i]];
		glm::vec3 endVertex = this->vertices[vertexPairs[i + 1]];

		std::vector<int> edgeVertexIndices(numDivisions + 2);
		edgeVertexIndices[0] = vertexPairs[i];

		// Add vertices along edge
		for (int divisionIndex = 0; divisionIndex < numDivisions; divisionIndex++)
		{
			float t = (divisionIndex + 1.0f) / (numDivisions + 1.0f);
			edgeVertexIndices[divisionIndex + 1] = (int)this->vertices.size();
			this->vertices.push_back(_slerp(startVertex, endVertex, t));
		}
		edgeVertexIndices[numDivisions + 1] = vertexPairs[i + 1];
		int edgeIndex = (int)i / 2;
		edges[edgeIndex] = Edge(edgeVertexIndices);
	}

	// Create faces
	for (size_t i = 0; i < edgeTriplets.size(); i += 3)
	{
		int faceIndex = (int)i / 3;
		bool reverse = faceIndex >= 4;
		_createFace(edges[edgeTriplets[i]], edges[edgeTriplets[i + 1]], edges[edgeTriplets[i + 2]], reverse);
	}

	// Smooth maximum of two values, controlled by smoothing factor k
	// When k = 0, this behaves identically to max(a, b)
	auto smoothMax = [&](float a, float b, float k) -> float {
		k = glm::min(0.0f, -k);
		float h = glm::max(0.0f, glm::min(1.0f, (b - a + k) / (2.0f * k)));
		return a * h + b * (1.0f - h) - k * h * (1.0f - h);
	};

	const float floorDepth = 10.0f;
	const float floorSmoothing = 0.5f;
	const float depthStrength = 30.0f;

	Noiser noiser;
	for(glm::vec3& vertex : this->vertices)
	{
		float value = noiser.getPerlinNoise(vertex, 8, 1.0f);
		float floorShape = -floorDepth + value * 0.15f;
		float floorValue = smoothMax(value, floorShape, floorSmoothing);
		floorValue *= (floorValue < 0.0f) ? 1.0f + depthStrength : 1.0f;

		float finalHeight = 1.0f + floorValue * 0.01f;

		vertex += glm::normalize(vertex) * finalHeight * radius;
	}

	// Calculate the normals
	this->normals.resize(this->vertices.size(), {0,0,0});
	for (const glm::u32vec3& tri : this->tris)
	{
		glm::vec3 v1 = this->vertices[tri.y] - this->vertices[tri.x];
		glm::vec3 v2 = this->vertices[tri.z] - this->vertices[tri.x];
		glm::vec3 n = cross(v1, v2);
		this->normals[tri.x] += n;
		this->normals[tri.y] += n;
		this->normals[tri.z] += n;
	}
	for (glm::vec3& n : this->normals)
	{
		n = glm::normalize(n);
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
