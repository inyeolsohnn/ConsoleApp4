#include "stdafx.h"
#include "Tile.h"




Tile::~Tile()
{
}

void Tile::draw(sf::RenderWindow & window, float dt)
{
	window.draw(this->sprite);
}
