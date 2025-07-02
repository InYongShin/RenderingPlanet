#ifndef RENDERMANAGER_HPP
#define RENDERMANAGER_HPP

#include "Singleton.hpp"
#include "RenderPass.hpp"
#include "DepthRenderPass.hpp"
#include "Scene.hpp"

#include <vector>

class RenderManager : public Singleton<RenderManager>
{
private:
	friend class Singleton;

	std::unique_ptr<DepthRenderPass> depthRenderPass;
	std::vector<std::unique_ptr<RenderPass>> renderPasses;

public:

	void addDepthRenderPass(std::unique_ptr<DepthRenderPass>& depthRenderPass);
	void addRenderPass(std::unique_ptr<RenderPass>& renderPass);

	void render();

	RenderManager() {}
	virtual ~RenderManager() {}
};

#endif /* RENDERMANAGER_HPP */
