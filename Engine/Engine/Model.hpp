#ifndef MODEL_HPP
#define MODEL_HPP

#include "Mesh.hpp"
#include "Program.hpp"
#include "GLTools.hpp"

class Model
{
private:
	glm::mat4 _modelMat = glm::mat4(1.f);

protected:
	glm::vec3 position = glm::vec3(0.f);
	Program program;
	Mesh mesh;

protected:
	bool isCreated = false;

public:

	void loadProgram(const char* vertexPath, const char* fragmentPath, 
					 const char* geometryPath = nullptr, const char* tessControlPath = nullptr, const char* tessEvaluatePath = nullptr);

	inline void setProgram(const Program& program) { this->program = program; }

	void setPosition(const glm::vec3& position);
	inline glm::vec3 getPosition() const { return this->position; }

	virtual void draw();

	void clear();

	Model() {}
	Model(const glm::vec3& position) { setPosition(position); }
	virtual ~Model() { clear(); }
};




#endif /* MODEL_HPP */