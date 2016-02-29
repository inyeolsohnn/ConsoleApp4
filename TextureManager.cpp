#include "stdafx.h"
#include "TextureManager.h"
#include <SFML/Graphics.hpp>
#include <map>
#include <string>

TextureManager::TextureManager()
{
}


TextureManager::~TextureManager()
{
}

void TextureManager::loadTexture(const std::string & name, const std::string & fileName)
{
	sf::Texture tex;
	tex.loadFromFile(fileName);

	this->textures[name] = tex;

}
sf::Texture& TextureManager::getRef(const std::string& name) {
	return this->textures.at(name);
}
