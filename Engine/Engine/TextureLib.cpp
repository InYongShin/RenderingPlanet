
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
		textures.emplace_back();
		textures.back().load(fileName);
		ret = (int)textures.size() - 1;
	}
	return ret;
}

void TextureLib::clear()
{
	this->textures.clear();
}
