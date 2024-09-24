#ifndef GROUND_HPP
#define GROUND_HPP

#include "GLTools.hpp"
#include "Model.hpp"

class Ground : public Model
{
private:
	glm::vec3 groundColor;

public:

	void createGroundMesh(const glm::vec2& size);
	void createGroundMesh(const glm::vec2& size, const int noiseWidth, const int noiseHeight);

	inline glm::vec3 getGroundColor() const { return this->groundColor; }
	inline void setGroundColor(const glm::vec3& color) { this->groundColor = color; }

	Ground() : groundColor(glm::vec3(0.f)) {}
	Ground(const glm::vec3& position, const glm::vec3& groundColor) : Model(position), groundColor(groundColor) {}
	virtual ~Ground() {}
};

#endif /* GROUND_HPP */