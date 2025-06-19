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
	int _depth = 0;
	int _numChannels = 0;
	void* _data = nullptr;

	GLuint _texID = 0;
	GLint _internalFormat = GL_RGB32UI;
	GLenum _format = GL_RGB;
	GLenum _type = GL_UNSIGNED_BYTE;

	GLuint _minFilter = GL_LINEAR;
	GLuint _wrap_s = GL_REPEAT;
	GLuint _wrap_t = GL_REPEAT;
	GLuint _wrap_r = GL_REPEAT;

	bool _isSrgb = false;

	bool _isNeedMaintainData = false;

	GLenum _target = GL_TEXTURE_2D;

	void setTexParam(GLuint minFilter = GL_LINEAR, GLuint wrap_s = GL_REPEAT, GLuint wrap_t = GL_REPEAT, GLuint wrap_r = GL_REPEAT);
	void createGL();

	static GLint getBinding2D()
	{
		GLint oldTexID = 0;
		glGetIntegerv(GL_TEXTURE_BINDING_2D, &oldTexID);
		return oldTexID;
	}
	static void restoreBinding2D(GLint oldTexID)
	{
		glBindTexture(GL_TEXTURE_2D, oldTexID);
	}

	static GLint getBinding3D()
	{
		GLint oldTexID = 0;
		glGetIntegerv(GL_TEXTURE_BINDING_3D, &oldTexID);
		return oldTexID;
	}
	static void restoreBinding3D(GLint oldTexID)
	{
		glBindTexture(GL_TEXTURE_3D, oldTexID);
	}
	
public:
	inline const std::string& getFileName() { return this->_fileName; }

	inline int getWidth() const { return this->_width; }
	inline int getHeight() const { return this->_height; }
	inline int getNumChannels() const { return this->_numChannels; }

	inline int getTexID() const { return this->_texID; }
	inline GLenum getInternalFormat() const { return this->_internalFormat; }
	inline GLenum getFormat() const { return this->_format; }
	inline GLenum getType() const { return this->_type; }

	void load2D(const std::string& filenName, const bool isSrgb = false, const bool isNeedMaintainData = false);

	void create(int width, int height, GLenum type = GL_UNSIGNED_BYTE, int numChannels = 4, bool isSrgb = false, bool isNeedMaintainData = false);

	void setTextureData2D(const int width, const int height, const GLenum type, const int numChannels, void* data);
	void setTextureData3D(const int width, const int height, const int depth, const GLenum type, const int numChannels, void* data);

	void bind(int slot);
	void bind(int slot, const std::shared_ptr<Program>& program, const std::string& name);

	bool isUsable() const { return this->_texID > 0; }

	void clear();

	Texture() {}
	Texture(Texture&& other) noexcept
		: _fileName(std::move(other._fileName)), _width(other._width), _height(other._height), _numChannels(other._numChannels), _data(other._data),
		_texID(other._texID), _internalFormat(other._internalFormat), _format(other._format), _type(other._type),
		_minFilter(other._minFilter), _wrap_s(other._wrap_s), _wrap_t(other._wrap_t), _isSrgb(other._isSrgb), _isNeedMaintainData(other._isNeedMaintainData)
	{
		other._data = nullptr;
		other._texID = 0;
	}
	Texture(const std::string& fileName) 
	{
		load2D(fileName);
	}
	virtual ~Texture() { clear(); }
};


#endif /* TEXTURE_HPP */
