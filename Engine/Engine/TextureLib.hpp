#ifndef TEXTURELIB_HPP
#define TEXTURELIB_HPP

#include "Texture.hpp"

#include <vector>
#include <string>

class TextureLib
{
private:
	std::vector<Texture> textures;

public:

	int searchTexture(const std::string& fileName);
	int loadTexture(const std::string& fileName);

	size_t size() const { return textures.size(); }
	Texture& operator[] (int i) { return textures[i]; }
	const Texture& operator[] (int i) const { return textures[i]; }

	void clear();
};

#endif /* TEXTURELIB_HPP */
