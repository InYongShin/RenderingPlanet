#ifndef RENDERPASS_HPP
#define RENDERPASS_HPP

#include "GLTools.hpp"
#include "Program.hpp"

#include <memory>

class RenderPass
{
private:
	std::shared_ptr<Program> program;
	GLuint vao, eBuf;
	GLsizei nTris;
	GLenum drawMode;

public:

	inline std::shared_ptr<Program> getProgram() const { return this->program; }
	inline void setProgram(const std::shared_ptr<Program>& program) { this->program = program; }

	void setState();
	void setVertexData(GLuint vao, GLuint eBuf, GLsizei nTris, GLenum drawMode = GL_TRIANGLES);

	void draw();

	RenderPass() : vao(0), eBuf(0), nTris(0), drawMode(GL_TRIANGLES) {}
	virtual ~RenderPass() {};
};

#endif /* RENDERPASS_HPP */
