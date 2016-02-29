#pragma once
#include "BoundingBox.h"
#include <vector>
class Collidable
{
public:
	Collidable();
	virtual ~Collidable();
	virtual void collide(Collidable* collidee) = 0;
	std::vector<Collidable*> collidedList;
	bool expired = false;
	Moo::BoundingBox bound;

};

