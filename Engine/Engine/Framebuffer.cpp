
#include "Framebuffer.hpp"

#include <vector>

void Framebuffer::storeFramebufferState()
{
	prevState.capture();
	glDisable( GL_SCISSOR_TEST );
}

void Framebuffer::restoreFramebufferState()
{
	prevState.restore();
}

void Framebuffer::create(int w, int h, GLenum type, int nChannels, bool withDepthBuffer)
{
	this->width = w;
	this->height = h;
	this->numChannels = nChannels;
	this->depthed = withDepthBuffer;
	// auto [internal,format,_type] = TextureManager::getInstance()->getTextureType(type, numChannels, false );
	clearTextures();
	storeFramebufferState();

	glErr("Before create fbo texture");
	if(this->colorTex.getTexID() < 1) {
		this->colorTex.create(this->width, this->height, type, this->numChannels, false, false);
	}
	if(this->depthed) {
		this->depthTex.create(this->width, this->height, GL_FLOAT, 1, false, false);

		// TODO : Depth Component
		/*
		if( dataType == GL_FLOAT )
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32F, width, height,
		0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
		else
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, width, height,
		0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
		*/
	}
	if(this->id < 1) {
		glGenFramebuffers(1, &this->id);
	}

	// TODO: multiple color attachments
	glBindFramebuffer(GL_FRAMEBUFFER, this->id);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, this->colorTex.getTexID(), 0);
	glErr("after glFramebufferTexture2D: colorTex");
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, this->depthTex.getTexID(), 0);
	glErr("after glFramebufferTexture2D: depthTex");
	std::vector<GLenum> drawBuffers = {GL_COLOR_ATTACHMENT0};
	glDrawBuffers(1, drawBuffers.data());
	glErr("after glDrawBuffers");
	GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	if(status !=GL_FRAMEBUFFER_COMPLETE)
	{
		std::cerr << "FBO is not completed!!\n";
	}

	restoreFramebufferState();
}

void Framebuffer::use()
{
	storeFramebufferState();
	glBindFramebuffer(GL_FRAMEBUFFER, this->id);
	glViewport(0, 0, this->width, this->height);
}

void Framebuffer::unuse()
{
	restoreFramebufferState();
}

unsigned char* Framebuffer::readPixels()
{
	if(this->colorTex.getTexID() < 1)
	{
		return nullptr;
	}

	// TODO: define the format and type. Texture or Framebuffer?

	storeFramebufferState();
	unsigned char* data = new unsigned char[this->width * this->height * this->numChannels];
	
	glBindFramebuffer(GL_FRAMEBUFFER, this->id);
	glReadPixels(0, 0, this->width, this->height, this->colorTex.getFormat(), this->colorTex.getType(), data);

	restoreFramebufferState();

	return data;
}

void Framebuffer::clearTextures()
{
	if(this->id > 0)
	{
		glDeleteFramebuffers(1, &this->id);
		this->colorTex.clear();
		this->id = 0;
	}

	if(this->depthed)
	{
		this->depthTex.clear();
		this->depthed = false;
	}
}

void Framebuffer::clear()
{
	clearTextures();

	this->width = 0;
	this->height = 0;
	this->numChannels = 0;
}

Framebuffer::Framebuffer(int w, int h, GLenum type, int nChannels, bool withDepthBuffer /*= false*/)
{
	create(w, h, type, nChannels, withDepthBuffer);
}
