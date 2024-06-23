#include "TextureManager.hpp"

int TextureManager::loadTexture(const std::string& fileName)
{
	return this->textureLib.loadTexture(fileName);
}
