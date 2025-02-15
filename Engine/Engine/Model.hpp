#ifndef MODEL_HPP
#define MODEL_HPP

#include "Mesh.hpp"
#include "Program.hpp"
#include "GLTools.hpp"

#include <memory>

class Model
{
private:
	glm::mat4 _modelMat = glm::mat4(1.f);

	std::vector<int> texIDs;
	std::vector<std::string> shaderNames;

protected:
	glm::vec3 position = glm::vec3(0.f);
	Mesh mesh;

	bool isCreated = false;

public:

	void loadProgram(const char* vertexPath, const char* fragmentPath, 
					 const char* geometryPath = nullptr, const char* tessControlPath = nullptr, const char* tessEvaluatePath = nullptr);

	void setPosition(const glm::vec3& position);
	inline glm::vec3 getPosition() const { return this->position; }

	void addTexture(int id, const std::string& shaderName);

	const Mesh& getMesh() const { return this->mesh; }

	virtual void draw();

	void clear();

	Model() {}
	Model(const glm::vec3& position) { setPosition(position); }
	virtual ~Model() { clear(); }
};

#endif /* MODEL_HPP */