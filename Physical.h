#pragma once
#include <SFML/Graphics.hpp>
#include "Collidable.h"
class Physical : public Collidable
{
public:
	//physical entities without inputs eg. bullets. 
	
	Physical();
	virtual ~Physical();
	virtual void update(float dt) = 0;
	virtual void draw(sf::RenderWindow& window, float dt) = 0;
};

