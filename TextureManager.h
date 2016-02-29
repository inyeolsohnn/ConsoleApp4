#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include <SFML/Graphics.hpp>
#include <string>
#include <map>
class TextureManager
{
private:
	std::map<std::string, sf::Texture> textures;
public:
	TextureManager();
	~TextureManager();
	void loadTexture(const std::string& name, const std::string& fileName);
	sf::Texture& getRef(const std::string& textureName);
};
#endif
