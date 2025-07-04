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
	int setTexture2D(const int width, const int height, const GLenum type, const int numChannels, void* data);
	int setTexture3D(const int width, const int height, const int depth, const GLenum type, const int numChannels, void* data);

	size_t size() const { return this->textures.size(); }
	Texture& operator[] (int i) { return this->textures[i]; }
	const Texture& operator[] (int i) const { return this->textures[i]; }

	void clear();
};

#endif /* TEXTURELIB_HPP */
