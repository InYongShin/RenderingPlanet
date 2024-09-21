#ifndef TEXTUREMANAGER_HPP
#define TEXTUREMANAGER_HPP

#include "Singleton.hpp"

#include "TextureLib.hpp"

#include <string>

class TextureManager : public Singleton<TextureManager>
{
private:
	friend class Singleton;

	TextureLib textureLib;
public:

	int loadTexture(const std::string& fileName);
	int setTexture(const int width, const int height, const GLenum type, const int numChannels, unsigned char* data);

	Texture& getTexture(int id) { return textureLib[id]; }
	const Texture& getTexture(int id) const { return textureLib[id]; }

	std::tuple<GLenum,GLenum,GLenum> getTextureType(GLenum type, int numChannels, bool sRGB = false);

	TextureManager() {}
	virtual ~TextureManager() {}
};


#endif /* TEXTUREMANAGER_HPP */