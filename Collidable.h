#pragma once
#include "BoundingBox.h"
#include <vector>
#include <SFML/Graphics.hpp>
class Collidable
{
public:
	Collidable();
	Collidable(Moo::BoundingBox box) :bound(box) {

	}
	virtual ~Collidable();
	virtual void collide(Collidable* collidee) = 0;
	std::vector<Collidable*> collidedList;
	bool expired = false;
	Moo::BoundingBox bound;
	virtual void draw(sf::RenderWindow& window, float dt) = 0;
	virtual void drawShadow(sf::RenderWindow& window, float dt) = 0;
};

