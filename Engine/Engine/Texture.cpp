
#include "Texture.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

std::tuple<GLenum,GLenum,GLenum> Texture::getTextureType(GLenum type, int numChannels, bool sRGB /*= false*/)
{
	switch(type)
	{
		case GL_UNSIGNED_SHORT:
		{
			switch(numChannels)
			{
				case 1: return {GL_R16UI, GL_RED, type};
				case 2:	return {GL_RG16UI, GL_RG, type};
				case 4:	return {GL_RGBA16UI, GL_RGBA, type};
				case 3:
				default: return {GL_RGB16UI, GL_RGB, type};
			}
			break;
		}
		case GL_UNSIGNED_INT:
		{
			switch(numChannels)
			{
				case 1:	return {GL_R32UI, GL_RED, type};
				case 2:	return {GL_RG32UI, GL_RG, type};
				case 4:	return {GL_RGBA32UI, GL_RGBA, type};
				case 3:
				default: return {GL_RGB32UI, GL_RGB, type};
			}
			break;
		}
		case GL_FLOAT:
		{
			switch(numChannels)
			{
				case 1:	return {GL_R32F, GL_RED, type};
				case 2:	return {GL_RG32F, GL_RG, type};
				case 4:	return {GL_RGBA32F, GL_RGBA, type};
				case 3:
				default: return {GL_RGB32F, GL_RGB, type};
			}
			break;
		}
		case GL_UNSIGNED_BYTE:
		default:
		{
			switch(numChannels)
			{
				case 1:	return {GL_R8, GL_RED, type};
				case 2:	return {GL_RG8, GL_RG, type};
				case 4:	return {GLenum(sRGB?GL_SRGB8_ALPHA8:GL_RGBA8), GL_RGBA, type};
				case 3:
				default: return {GLenum(sRGB?GL_SRGB8:GL_RGB8), GL_RGB, type};
			}
			break;
		}
	}
}

void Texture::setTexParam(GLuint minFilter /*= GL_LINEAR*/, GLuint wrap_s /*= GL_REPEAT*/, GLuint wrap_t /*= GL_REPEAT*/)
{
	float maxAniso;
	glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &maxAniso);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY, maxAniso);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap_s);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap_t);
}

void Texture::load(const std::string& fileName, const bool isSrgb /*= false*/, const bool isNeedMaintainData /*= false*/)
{
	std::cout << "Loading texture: " << fileName << "\n";
	
	int width=0, height=0, numChannels=0;
	this->_isSrgb = isSrgb;
	this->_isNeedMaintainData = isNeedMaintainData;

	stbi_set_flip_vertically_on_load(true);

	this->_data = stbi_load(fileName.c_str(), &width, &height, &numChannels, 0);
	if (this->_data == nullptr)
	{
		std::cerr << "Failed to load texture: " << fileName << std::endl;
		return;
	}

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

	// TODO: type
	auto [internalFormat, format, type] = getTextureType(this->_type, this->_numChannels, this->_isSrgb);
	GLint oldTexID = Texture::getBinding();
	
	glGenTextures(1, &this->_texID);
	glBindTexture(GL_TEXTURE_2D, this->_texID);
	setTexParam(this->_minFilter, this->_wrap_s, this->_wrap_t);
	glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, this->_width, this->_height, 0, format, type, this->_data);
	glGenerateMipmap(GL_TEXTURE_2D);
	Texture::restoreBinding(oldTexID);

	if (this->_data != nullptr && this->_isNeedMaintainData == false)
	{
		delete this->_data;
		this->_data = nullptr;
	}
}

void Texture::bind(int slot)
{
	if (this->_texID < 1)
	{
		std::cerr << "Texture is not loaded" << std::endl;
		return;
	}
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, this->_texID);
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
