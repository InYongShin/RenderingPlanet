#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include "GLTools.hpp"
#include "Program.hpp"

#include <iostream>
#include <string>

class Texture
{
private:
	std::string _fileName = "";

	int _width = 0;
	int _height = 0;
	int _numChannels = 0;
	unsigned char* _data = nullptr;

	GLuint _texID = 0;
	GLint _internalFormat = GL_RGB32UI;
	GLenum _format = GL_RGB;
	GLenum _type = GL_UNSIGNED_BYTE;

	GLuint _minFilter = GL_LINEAR;
	GLuint _wrap_s = GL_REPEAT;
	GLuint _wrap_t = GL_REPEAT;

	bool _isSrgb = false;

	bool _isNeedMaintainData = false;

	std::tuple<GLenum,GLenum,GLenum> getTextureType(GLenum type, int numChannels, bool sRGB = false);
	void setTexParam(GLuint minFilter = GL_LINEAR, GLuint wrap_s = GL_REPEAT, GLuint wrap_t = GL_REPEAT);
	void createGL();

	static GLint getBinding()
	{
		GLint oldTexID = 0;
		glGetIntegerv(GL_TEXTURE_BINDING_2D, &oldTexID);
		return oldTexID;
	}
	static void restoreBinding(GLint oldTexID)
	{
		glBindTexture(GL_TEXTURE_2D, oldTexID);
	}
	
public:
	inline const std::string& getFileName() { return this->_fileName; }

	inline int getWidth() const { return this->_width; }
	inline int getHeight() const { return this->_height; }
	inline int getNumChannels() const { return this->_numChannels; }

	inline int getTexID() const { return this->_texID; }

	void load(const std::string& filenName, const bool isSrgb = false, const bool isNeedMaintainData = false);

	void bind(int slot);
	void bind(int slot, const std::shared_ptr<Program>& program, const std::string& name);

	bool isUsable() const { return this->_texID > 0; }

	void clear();

	Texture() {}
	Texture(const std::string& fileName) 
	{
		load(fileName);
	}
	virtual ~Texture() { clear(); }
};


#endif /* TEXTURE_HPP */
