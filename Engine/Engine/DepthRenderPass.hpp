#ifndef DEPTHRENDERPASS_HPP
#define DEPTHRENDERPASS_HPP

#include "RenderPass.hpp"

#include <memory>

class DepthRenderPass : public RenderPass
{
private:
	std::shared_ptr<Program> depthProgram;

public:

	const GLuint getDepthTexID() const override;

	void setState() override;

	void draw() override;

	DepthRenderPass(const int width, const int height);
	virtual ~DepthRenderPass() {};
};

#endif /* DEPTHRENDERPASS_HPP */
