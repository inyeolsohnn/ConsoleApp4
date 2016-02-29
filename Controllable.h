#pragma once
#include<SFML/Graphics.hpp>
#include "Collidable.h"
class Controllable : public Collidable
{
public:
	Controllable();
	virtual ~Controllable();
	std::vector<Collidable*> collidedList;
	virtual void update(float dt) = 0;
	virtual void draw(sf::RenderWindow& window, float dt) = 0;
	virtual void handleInput(sf::Event event) = 0;
};

