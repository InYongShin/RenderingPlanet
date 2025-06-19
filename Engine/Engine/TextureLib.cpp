
#include "TextureLib.hpp"

int TextureLib::searchTexture(const std::string& fileName)
{
	for(size_t i = 0; i < this->textures.size(); ++i)
	{
		if(fileName.compare(this->textures[i].getFileName()) == 0)
		{
			return int(i);
		}
	}
	return -1;
}

int TextureLib::loadTexture(const std::string& fileName)
{
	int ret = searchTexture(fileName);
	if(ret < 0)
	{
		this->textures.emplace_back();
		this->textures.back().load(fileName);
		ret = (int)this->textures.size() - 1;
	}
	return ret;
}

int TextureLib::setTexture2D(const int width, const int height, const GLenum type, const int numChannels, unsigned char* data)
{
	this->textures.emplace_back();
	this->textures.back().setTextureData2D(width, height, type, numChannels, data);
	return (int)this->textures.size() - 1;
}

int TextureLib::setTexture3D(const int width, const int height, const int depth, const GLenum type, const int numChannels, unsigned char* data)
{
	this->textures.emplace_back();
	this->textures.back().setTextureData3D(width, height, depth, type, numChannels, data);
	return (int)this->textures.size() - 1;
}

void TextureLib::clear()
{
	this->textures.clear();
}
