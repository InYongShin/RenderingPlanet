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
	int setTexture(const int width, const int height, const GLenum type, const int numChannels, unsigned char* data);

	size_t size() const { return this->textures.size(); }
	Texture& operator[] (int i) { return this->textures[i]; }
	const Texture& operator[] (int i) const { return this->textures[i]; }

	void clear();
};

#endif /* TEXTURELIB_HPP */
