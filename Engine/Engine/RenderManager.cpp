#include "RenderManager.hpp"

void RenderManager::addDepthRenderPass(std::unique_ptr<DepthRenderPass>& depthRenderPass)
{
	if (depthRenderPass == nullptr)
	{
		std::cerr << "DepthRenderPass is nullptr" << std::endl;
		return;
	}

	this->depthRenderPass = std::move(depthRenderPass);
}

void RenderManager::addRenderPass(std::unique_ptr<RenderPass>& renderPass)
{
	if (renderPass == nullptr)
	{
		std::cerr << "RenderPass is nullptr" << std::endl;
		return;
	}

	this->renderPasses.push_back(std::move(renderPass));
}

void RenderManager::render()
{
	GLuint depthMapID = 0;
	if (this->depthRenderPass)
	{
		this->depthRenderPass->draw();

		depthMapID = this->depthRenderPass->getDepthTexID();
	}

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	for (const auto& renderPass : this->renderPasses)
	{
		if (depthMapID > 0)
		{
			renderPass->setDepthTexID(depthMapID);
		}

		renderPass->draw();
	}
}
