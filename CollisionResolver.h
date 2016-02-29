#pragma once
#include"Collidable.h"
class CollisionResolver
{
public:
	CollisionResolver();
	~CollisionResolver();
	void resolveCollision(Collidable& c1, Collidable& c2);
};

