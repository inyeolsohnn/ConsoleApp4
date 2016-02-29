#ifndef TILE_HPP
#define	TILE_HPP 
#include <SFML\Graphics.hpp>
#include "Animation.h"
#include "AnimationManager.h"

enum class TileType{DIRT};
class Tile
{
public:
	unsigned int level;
	unsigned int height;
	unsigned int width;
	AnimationManager animMgr;
	sf::Sprite sprite;
	Tile() {};
	Tile(const unsigned int width, const unsigned int height, const unsigned int level, sf::Texture& texture, const std::vector<Animation>& animations) {
		this->level = level;
		this->height = height;
		this->width = width;
		sprite.setTextureRect(sf::IntRect(0, 0, this->width, this->height));
			
		this->sprite.setTexture(texture);
		for (auto animation : animations) {
			this->animMgr.addAnim(animation);
		}

	}
	~Tile();
	void draw(sf::RenderWindow& window, float dt);
	

};
#endif
