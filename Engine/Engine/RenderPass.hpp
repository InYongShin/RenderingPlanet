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

	std::vector<std::shared_ptr<Model>> models;

	GLboolean depthTest;
	GLboolean cullFace;

public:

	inline std::vector<std::shared_ptr<Model>> getModels() const { return this->models; }

	void setState();

	void addModel(const std::shared_ptr<Model>& model);

	void draw();

	void onDepthTest();
	void offDepthTest();
	void onCullFace();
	void offCullFace();

	RenderPass() : depthTest(GL_TRUE), cullFace(GL_TRUE) {}
	virtual ~RenderPass() {};
};

#endif /* RENDERPASS_HPP */
