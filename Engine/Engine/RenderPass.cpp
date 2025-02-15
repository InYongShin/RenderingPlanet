#include "RenderPass.hpp"

void RenderPass::loadProgram(const char* vertexPath, const char* fragmentPath, const char* geometryPath, const char* tessControlPath, const char* tessEvaluatePath)
{
	std::shared_ptr<Program> prog = std::make_shared<Program>(vertexPath, fragmentPath, geometryPath, tessControlPath, tessEvaluatePath);
	if (prog->isUsable() == false)
	{
		assert(false);
		std::cerr << "Error loading program" << std::endl;
		return;
	}
	
	setProgram(prog);
}

void RenderPass::setState()
{
	if (this->program == nullptr)
	{
		std::cerr << "Program is nullptr" << std::endl;
		return;
	}

	// TODO: State 包府
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void RenderPass::addModel(const std::shared_ptr<Model>& model)
{
	if (model == nullptr)
	{
		std::cerr << "Model is nullptr" << std::endl;
		return;
	}

	this->models.push_back(model);
}

void RenderPass::setModelVertexData(const std::shared_ptr<Model>& model)
{
	if (model == nullptr)
	{
		std::cerr << "Model is nullptr" << std::endl;
		return;
	}

	const Mesh& mesh = model->getMesh();
	this->vao = mesh.vao;
	this->eBuf = mesh.eBuf;
	this->nTris = mesh.nTris;
	this->drawMode = mesh.primitive;
}

void RenderPass::setVertexData(GLuint vao, GLuint eBuf, GLsizei nTris, GLenum drawMode /* = GL_TRIANGLES */)
{
	this->vao = vao;
	this->eBuf = eBuf;
	this->nTris = nTris;
	this->drawMode = drawMode;
}

void RenderPass::draw()
{
	for(const auto& model : this->models)
	{
		if (model == nullptr)
		{
			std::cerr << "Model is nullptr" << std::endl;
			continue;
		}

		// TODO: Primitive 包府
		const Mesh& mesh = model->getMesh();
		glBindVertexArray(mesh.vao);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.eBuf);
		glDrawElements(mesh.primitive, mesh.nTris * 3, GL_UNSIGNED_INT, 0);
	}

	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
