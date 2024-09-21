#ifndef FRAMEBUFFER_HPP
#define FRAMEBUFFER_HPP

#include "GLTools.hpp"
#include "Texture.hpp"

class Framebuffer
{
private:
	struct _PREV_STATE_ {
		GLint  drawFboId = 0, readFboId = 0;
		GLint  viewport[4];
		GLint  scissor[4];
		GLint  cullMode = GL_BACK;
		GLint  cullFace = GL_FALSE;
		GLint  depthTest = GL_FALSE;
		GLint  scissorTest = GL_FALSE;
		void capture() {
			glGetIntegerv(GL_DRAW_FRAMEBUFFER_BINDING, &drawFboId);
			glGetIntegerv(GL_READ_FRAMEBUFFER_BINDING, &readFboId);
			glGetIntegerv(GL_VIEWPORT, viewport);
			glGetIntegerv(GL_SCISSOR_BOX, scissor);
			glGetIntegerv(GL_CULL_FACE_MODE, &cullMode);

			cullFace = glIsEnabled(GL_CULL_FACE);
			depthTest = glIsEnabled(GL_DEPTH_TEST);
			scissorTest = glIsEnabled(GL_SCISSOR_TEST);
		}
		void restore() {
			glBindFramebuffer(GL_DRAW_FRAMEBUFFER, drawFboId);
			glBindFramebuffer(GL_READ_FRAMEBUFFER, readFboId);
			glViewport(viewport[0], viewport[1], viewport[2], viewport[3]);
			glScissor(scissor[0], scissor[1], scissor[2], scissor[3]);
			glCullFace(cullMode );

			if( cullFace )	glEnable (GL_CULL_FACE);
			else			glDisable(GL_CULL_FACE);
			if( depthTest )	glEnable (GL_DEPTH_TEST);
			else			glDisable(GL_DEPTH_TEST);
			if(scissorTest) glEnable (GL_SCISSOR_TEST);
			else			glDisable(GL_SCISSOR_TEST);
		}
	};

private:
	GLuint id = 0;
	_PREV_STATE_ prevState;

	int width = 0;
	int height = 0;
	int numChannels = 0;

	bool depthed = false;
	Texture depthTex;
	Texture colorTex;

public:

	void storeFramebufferState();
	void restoreFramebufferState();

	void create(int w, int h, GLenum type = GL_UNSIGNED_BYTE, int nChannels = 4, bool withDepthBuffer = false);

	void use();
	void unuse();

	unsigned char* readPixels();

	void clearTextures();
	void clear();

	Framebuffer() {}
	Framebuffer(int w, int h, GLenum type = GL_UNSIGNED_BYTE, int nChannels = 4, bool withDepthBuffer = false);
	virtual ~Framebuffer() { clear(); }

};

#endif /* FRAMEBUFFER_HPP */
