#include "stdafx.h"
#include "Projectile.h"
#include<iostream>
#include"Actor.h"

Projectile::Projectile()
{
	this->elapsed = sf::milliseconds(0.f);
	
}


Projectile::~Projectile()
{
	std::cout << "projectil destroyed" << std::endl;
}

void Projectile::setVelocity(float dx, float dy, float dz)
{
	this->dx = dx;
	this->dy = dy;
	this->dz = dz;
}

void Projectile::update(float dt)
{
	this->elapsed += sf::milliseconds(dt);
	if (this->elapsed >= sf::milliseconds(2000.f)) {
		expired = true;	
	}
	this->bound.setCenter();
	
	this->projectileBody->setPosition(this->bound.cent.x, this->bound.cent.y+this->bound.cent.z);
	this->bound.min.x += dx;
	this->bound.max.x += dx;
	this->bound.min.y += dy;
	this->bound.max.y += dy; 
	this->bound.min.z += dz;
	this->bound.max.z += dz;
}

void Projectile::draw(sf::RenderWindow & window, float dt)
{
	window.draw(*this->projectileBody);
}

void Projectile::collide(Collidable* collidee) {
	if (std::find(collidedList.begin(), collidedList.end(), collidee) == collidedList.end()) {
		//RTTI checking. Look for different design if possible.

		if (Actor* actor = dynamic_cast<Actor*>(collidee)) {
			if (collidee != this->castedBy) {
				std::cout << "Collided with another actor" << std::endl;
				actor->getDamaged(this->dmg);
				this->collidedList.push_back(collidee);
				this->expired = true;
			}
			else {
				std::cout << "Collided with own actor" << std::endl;
				this->collidedList.push_back(collidee);
			}
		}
	}
	
}
