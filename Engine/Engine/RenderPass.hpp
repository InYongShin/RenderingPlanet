#ifndef RENDERPASS_HPP
#define RENDERPASS_HPP

#include "GLTools.hpp"
#include "Program.hpp"
#include "Model.hpp"
#include "Framebuffer.hpp"

#include <memory>

class RenderPass
{
protected:
	std::shared_ptr<Framebuffer> framebuffer;
	std::vector<std::shared_ptr<Model>> models;

	GLuint depthTexID;

	GLboolean depthTest;
	GLboolean cullFace;

public:
	inline std::vector<std::shared_ptr<Model>> getModels() const { return this->models; }

	void addModel(const std::shared_ptr<Model>& model);

	void setDepthTexID(const GLuint texID);
	virtual const GLuint getDepthTexID() const;

	virtual void setState();
	void onDepthTest();
	void offDepthTest();
	void onCullFace();
	void offCullFace();

	virtual void draw();

	RenderPass() : depthTest(GL_TRUE), cullFace(GL_TRUE), depthTexID(0) {}
	virtual ~RenderPass() {};
};

#endif /* RENDERPASS_HPP */
