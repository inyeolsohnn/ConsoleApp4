#pragma once
#include<vector>
#include"Status.h"
#include"Physical.h"
#include "Collidable.h"
#include <memory>
#include<SFML/Graphics.hpp>
class Projectile: public Physical
{
public:
	Projectile();
	virtual ~Projectile();
	float dx;
	float dy;
	float dz;
	
	std::unique_ptr<sf::Shape> projectileBody;
	std::vector<Status> statusVec;
	std::string projectileName;
	sf::Time elapsed;
	int dmg;
	Actor* castedBy;
	void setVelocity(float dx, float dy, float dz);
	virtual void update(float dt);
	virtual void draw(sf::RenderWindow& window, float dt);
	virtual void collide(Collidable* collidee);
};

