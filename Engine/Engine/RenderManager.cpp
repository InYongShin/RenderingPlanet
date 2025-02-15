#include "RenderManager.hpp"

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
	for (const auto& renderPass : this->renderPasses)
	{
		renderPass->draw();
	}
}
