#ifndef RENDERPASS_HPP
#define RENDERPASS_HPP

#include "GLTools.hpp"
#include "Program.hpp"
#include "Model.hpp"
#include "Framebuffer.hpp"

#include <memory>

class RenderPass
{
private:
	std::shared_ptr<Framebuffer> framebuffer;
	std::shared_ptr<Program> program;
	GLuint vao, eBuf;
	GLsizei nTris;
	GLenum drawMode;

	std::vector<std::shared_ptr<Model>> models;

	GLboolean depthTest;
	GLboolean cullFace;

public:

	inline std::shared_ptr<Program> getProgram() const { return this->program; }
	inline void setProgram(const std::shared_ptr<Program>& program) { this->program = program; }

	inline std::vector<std::shared_ptr<Model>> getModels() const { return this->models; }

	void loadProgram(const char* vertexPath, const char* fragmentPath,
					 const char* geometryPath = nullptr, const char* tessControlPath = nullptr, const char* tessEvaluatePath = nullptr);

	void setState();

	void addModel(const std::shared_ptr<Model>& model);

	void setModelVertexData(const std::shared_ptr<Model>& model);
	void setVertexData(GLuint vao, GLuint eBuf, GLsizei nTris, GLenum drawMode = GL_TRIANGLES);

	void draw();

	void onDepthTest();
	void offDepthTest();
	void onCullFace();
	void offCullFace();

	RenderPass() : vao(0), eBuf(0), nTris(0), drawMode(GL_TRIANGLES), 
				   depthTest(GL_TRUE), cullFace(GL_TRUE) {}
	virtual ~RenderPass() {};
};

#endif /* RENDERPASS_HPP */
