
#include "Texture.hpp"
#include "TextureManager.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>


void Texture::setTexParam(GLuint minFilter /*= GL_LINEAR*/, GLuint wrap_s /*= GL_REPEAT*/, GLuint wrap_t /*= GL_REPEAT*/, GLuint wrap_r /*= GL_REPEAT*/)
{
	float maxAniso;
	glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &maxAniso);
	glTexParameterf(this->_target, GL_TEXTURE_MAX_ANISOTROPY, maxAniso);
	glTexParameteri(this->_target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(this->_target, GL_TEXTURE_MIN_FILTER, minFilter);
	glTexParameteri(this->_target, GL_TEXTURE_WRAP_S, wrap_s);
	glTexParameteri(this->_target, GL_TEXTURE_WRAP_T, wrap_t);
	if(this->_target == GL_TEXTURE_3D)
	{
		glTexParameteri(this->_target, GL_TEXTURE_WRAP_R, wrap_r);
	}
}

void Texture::load2D(const std::string& fileName, const bool isSrgb /*= false*/, const bool isNeedMaintainData /*= false*/)
{
	std::cout << "Loading texture: " << fileName << "\n";

	int width=0, height=0, numChannels=0;
	this->_isSrgb = isSrgb;
	this->_isNeedMaintainData = isNeedMaintainData;

	this->_data = stbi_load(fileName.c_str(), &width, &height, &numChannels, 0);
	if (this->_data == nullptr)
	{
		std::cerr << "Failed to load texture: " << fileName << std::endl;
		return;
	}

	this->_target = GL_TEXTURE_2D;
	this->_type = GL_UNSIGNED_BYTE;
	this->_fileName = fileName;
	this->_width = width;
	this->_height = height;
	this->_numChannels = numChannels;

	createGL();
}

void Texture::createGL()
{
	if (this->_texID > 0)
	{
		clear();
	}

	auto [internalFormat, format, type] = TextureManager::getInstance()->getTextureType(this->_type, this->_numChannels, this->_isSrgb);
	if (this->_target == GL_TEXTURE_2D)
	{
		GLint oldTexID = Texture::getBinding2D();
		glGenTextures(1, &this->_texID);
		glBindTexture(this->_target, this->_texID);
		setTexParam(this->_minFilter, this->_wrap_s, this->_wrap_t);
		glTexImage2D(this->_target, 0, internalFormat, this->_width, this->_height, 0, format, type, this->_data);
		glGenerateMipmap(this->_target);
		Texture::restoreBinding2D(oldTexID);
	}
	else if (this->_target == GL_TEXTURE_3D)
	{
		GLint oldTexID = Texture::getBinding3D();
		glGenTextures(1, &this->_texID);
		glBindTexture(this->_target, this->_texID);
		setTexParam(this->_minFilter, this->_wrap_s, this->_wrap_t, this->_wrap_r);
		glTexImage3D(this->_target, 0, internalFormat, this->_width, this->_height, this->_depth, 0, format, type, this->_data);
		glGenerateMipmap(this->_target);
		Texture::restoreBinding3D(oldTexID);
	}
	else
	{
		std::cerr << "Failed to create gl texture." << std::endl;
		return;
	}

	if (this->_data != nullptr && this->_isNeedMaintainData == false)
	{
		delete this->_data;
		this->_data = nullptr;
	}
}

void Texture::createGLDepth()
{
	if (this->_texID > 0)
	{
		clear();
	}

	GLuint internalFormat;
	if (this->_type == GL_UNSIGNED_BYTE)
	{
		internalFormat = GL_DEPTH_COMPONENT;
	}
	else if (this->_type == GL_FLOAT)
	{
		internalFormat = GL_DEPTH_COMPONENT32F;
	}
	else
	{
		std::cerr << "Failed to create gl texture." << std::endl;
		return;
	}

	if (this->_target == GL_TEXTURE_2D)
	{
		GLint oldTexID = Texture::getBinding2D();
		glGenTextures(1, &this->_texID);
		glBindTexture(this->_target, this->_texID);
		setTexParam(this->_minFilter, this->_wrap_s, this->_wrap_t);
		glTexImage2D(this->_target, 0, internalFormat, this->_width, this->_height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
		// glGenerateMipmap(this->_target);
		Texture::restoreBinding2D(oldTexID);
	}
	else
	{
		std::cerr << "Failed to create depth texture." << std::endl;
		return;
	}
}

void Texture::create(int width, int height, GLenum type /*= GL_UNSIGNED_BYTE*/, int numChannels /*= 4*/, bool isSrgb /*= false*/, bool isNeedMaintainData /*= false*/)
{
	this->_target = GL_TEXTURE_2D;
	this->_width = width;
	this->_height = height;
	this->_numChannels = numChannels;
	this->_type = type;
	this->_isSrgb = isSrgb;
	this->_isNeedMaintainData = isNeedMaintainData;

	createGL();
}

void Texture::createDepth(int width, int height, GLenum type /*= GL_UNSIGNED_BYTE*/)
{
	this->_target = GL_TEXTURE_2D;
	this->_width = width;
	this->_height = height;
	this->_numChannels = 1;
	this->_type = type;
	this->_isSrgb = false;
	this->_isNeedMaintainData = false;

	createGLDepth();
}

void Texture::setTextureData2D(const int width, const int height, const GLenum type, const int numChannels, void* data)
{
	this->_target = GL_TEXTURE_2D;
	this->_width = width;
	this->_height = height;
	this->_numChannels = numChannels;
	this->_type = type;
	this->_data = data;
	this->_isNeedMaintainData = true;

	createGL();
}

void Texture::setTextureData3D(const int width, const int height, const int depth, const GLenum type, const int numChannels, void* data)
{
	this->_target = GL_TEXTURE_3D;
	this->_width = width;
	this->_height = height;
	this->_depth = depth;
	this->_numChannels = numChannels;
	this->_type = type;
	this->_data = data;
	this->_isNeedMaintainData = true;

	createGL();
}

void Texture::bind(int slot)
{
	if (this->_texID < 1)
	{
		std::cerr << "Texture is not loaded" << std::endl;
		return;
	}
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(this->_target, this->_texID);
}

void Texture::bind(int slot, const std::shared_ptr<Program>& program, const std::string& name)
{
	if (this->_texID < 1)
	{
		std::cerr << "Texture is not loaded" << std::endl;
		return;
	}

	if (program->isUsable() == false)
	{
		std::cerr << "Program is not usable" << std::endl;
		return;
	}

	bind(slot);
	program->setUniform(name, slot);
}

void Texture::clear()
{
	if (this->_texID > 0)
	{
		glDeleteTextures(1, &this->_texID);
		this->_texID = 0;
	}

	this->_width = 0;
	this->_height = 0;
	this->_numChannels = 0;

	if (this->_data != nullptr)
	{
		delete this->_data;
		this->_data = nullptr;
	}
}
