#include "DepthRenderPass.hpp"

#include "SceneManager.hpp"

const GLuint DepthRenderPass::getDepthTexID() const /*override*/
{
	if (this->framebuffer == nullptr)
	{
		return 0;
	}

	return this->framebuffer->getDepthTexID();
}

void DepthRenderPass::setState() /*override*/
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
}

void DepthRenderPass::draw() /*override*/
{
	if (this->depthProgram == nullptr || !this->depthProgram->isUsable())
	{
		return;
	}

	setState();

	this->framebuffer->use();
	glClear(GL_DEPTH_BUFFER_BIT);

	this->depthProgram->use();

	// TODO: 다양한 시점에 대응
	this->depthProgram->setUniform("viewMat", SceneManager::getInstance()->getCamera().viewMat());
	this->depthProgram->setUniform("projMat", SceneManager::getInstance()->getCamera().projMat());

	for (const auto& model : this->models)
	{
		if (model == nullptr)
		{
			std::cerr << "Model is nullptr" << std::endl;
			continue;
		}

		this->depthProgram->setUniform("modelMat", model->getModelMat());

		// TODO: Primitive 관리
		const Mesh& mesh = model->getMesh();
		glBindVertexArray(mesh.vao);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.eBuf);
		glDrawElements(mesh.primitive, mesh.nTris * 3, GL_UNSIGNED_INT, 0);
	}

	this->framebuffer->unuse();

	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

DepthRenderPass::DepthRenderPass(const int width, const int height)
	: RenderPass()
{
	// TODO: shader lib
	this->depthProgram = std::make_shared<Program>("Shader/depth.vert", "Shader/depth.frag");

	this->framebuffer = std::make_shared<Framebuffer>();
	this->framebuffer->createDepth(width, height, GL_FLOAT);
}
