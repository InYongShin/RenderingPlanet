#ifndef MODEL_HPP
#define MODEL_HPP

#include "Mesh.hpp"
#include "Program.hpp"

class Model
{
private:

protected:
	Program program;
	Mesh mesh;

public:

	void loadProgram(const char* vertexPath, const char* fragmentPath, 
					 const char* geometryPath = nullptr, const char* tessControlPath = nullptr, const char* tessEvaluatePath = nullptr);

	inline void setProgram(const Program& program) { this->program = program; }

	virtual void draw();

	void clear();

	Model() {}
	virtual ~Model() { clear(); }
};




#endif /* MODEL_HPP */