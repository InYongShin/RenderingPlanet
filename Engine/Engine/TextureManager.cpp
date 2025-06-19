#include "TextureManager.hpp"

int TextureManager::loadTexture(const std::string& fileName)
{
	return this->textureLib.loadTexture(fileName);
}

int TextureManager::setTexture2D(const int width, const int height, const GLenum type, const int numChannels, unsigned char* data)
{
	return this->textureLib.setTexture2D(width, height, type, numChannels, data);
}

int TextureManager::setTexture3D(const int width, const int height, const int depth, const GLenum type, const int numChannels, unsigned char* data)
{
	return this->textureLib.setTexture3D(width, height, depth, type, numChannels, data);
}

std::tuple<GLenum,GLenum,GLenum> TextureManager::getTextureType(GLenum type, int numChannels, bool sRGB /*= false*/)
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