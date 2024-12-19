#include "RenderPass.hpp"

void RenderPass::setState()
{
	if (this->program == nullptr)
	{
		std::cerr << "Program is nullptr" << std::endl;
		return;
	}

	// TODO: State °ü¸®
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
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
	glBindVertexArray(this->vao);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->eBuf);
	glDrawElements(GL_TRIANGLES, this->nTris*3, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
