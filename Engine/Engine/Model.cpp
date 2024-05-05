
#include "Model.hpp"

void Model::loadProgram(const char* vertexPath, const char* fragmentPath, const char* geometryPath /*= nullptr*/, const char* tessControlPath /*= nullptr*/, const char* tessEvaluatePath /*= nullptr*/)
{
	program.loadShaders(vertexPath, vertexPath, geometryPath, tessControlPath, tessEvaluatePath);
	if (program.isUsable() == false)
	{
		assert(false);
		std::cerr << "Error loading program" << std::endl;
	}
}

void Model::draw()
{
	if(this->program.isUsable() == false)
	{
		// TODO: Load default program
		// ex) program.loadShaders("shaders/default.vert", "shaders/default.frag");
	}
	this->program.use();

	glBindVertexArray(this->mesh.vao);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->mesh.eBuf);
	glDrawElements(GL_TRIANGLES, this->mesh.nTris*3, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Model::clear()
{
	program.clear();
	mesh.clear();
}
