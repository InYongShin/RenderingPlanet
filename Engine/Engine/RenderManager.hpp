#ifndef RENDERMANAGER_HPP
#define RENDERMANAGER_HPP

#include "Singleton.hpp"
#include "RenderPass.hpp"

#include <vector>

class RenderManager : public Singleton<RenderManager>
{
private:
	friend class Singleton;

	std::vector<std::unique_ptr<RenderPass>> renderPasses;

public:

	void addRenderPass(std::unique_ptr<RenderPass>& renderPass);

	void render();

	RenderManager() {}
	virtual ~RenderManager() {}
};

#endif /* RENDERMANAGER_HPP */
