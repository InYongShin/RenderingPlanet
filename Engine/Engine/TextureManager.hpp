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
	Texture& getTexture(int id) { return textureLib[id]; }
	const Texture& getTexture(int id) const { return textureLib[id]; }

	TextureManager() {}
	virtual ~TextureManager() {}
};


#endif /* TEXTUREMANAGER_HPP */