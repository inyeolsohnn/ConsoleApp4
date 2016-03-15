#include "stdafx.h"
#include "CharacterMovingState.h"
#include "CharacterActionState.h"
#include <iostream>




CharacterMovingState::CharacterMovingState(Actor * actor):CharacterState(actor)
{
	this->charStateType = CharacterState::CharacterStateType::Move;	
	this->moving = false;
	this->rotatable = true;
	this->movable = true;
}



void CharacterMovingState::handleInput(sf::Event event)
{
	switch (event.type) {
	case sf::Event::KeyPressed:
	{
		moving = true;
		if (event.key.code == sf::Keyboard::Right) {
			std::cout << "right" << std::endl;
			this->actor->moving_right = true;
			
		}
		if (event.key.code == sf::Keyboard::Left) {
			std::cout << "left" << std::endl;
			this->actor->moving_left = true;
		}
		if (event.key.code == sf::Keyboard::Up) {
			this->actor->moving_up = true;
		}
		if (event.key.code == sf::Keyboard::Down) {
			this->actor->moving_down = true;
		}
		if (event.key.code == sf::Keyboard::Z&&!this->actor->jumping) {
			if (movable) {
				std::cout << "Jump key pressed" << std::endl;
				this->actor->jumping = true;

				jump();
			}
		}
		break;
	}
	case sf::Event::KeyReleased: {
		
		if (event.key.code == sf::Keyboard::Right) {
			this->actor->moving_right = false;
		}
		if (event.key.code == sf::Keyboard::Left) {
			this->actor->moving_left = false;
		}
		if (event.key.code == sf::Keyboard::Up) {
				this->actor->moving_up = false;
		}
		if (event.key.code == sf::Keyboard::Down) {
				this->actor->moving_down = false;
		}
		
		break;

		}
	default:
		break;
	}
	
	
}

void CharacterMovingState::update(float dt)
{
	
		if((actor->moving_down||actor->moving_left||actor->moving_right||actor->moving_up)){
			moving = true;
		}
		else {
			moving = false;
		}
		

		if (rotatable) {
			if (this->actor->moving_right&&this->actor->moving_down) {
				this->actor->facing.x = 1.f;
				this->actor->facing.y = 1.f;
				this->actor->facing.z = 0.f;		

			}
			else if (this->actor->moving_right&&this->actor->moving_up) {
				this->actor->facing.x = 1.f;
				this->actor->facing.y = -1.f;
				this->actor->facing.z = 0.f;
			}
			else if (this->actor->moving_left&&this->actor->moving_down) {
				this->actor->facing.x = -1.f;
				this->actor->facing.y = 1.f;
				this->actor->facing.z = 0.f;
			}
			else if (this->actor->moving_left&&this->actor->moving_up) {
				this->actor->facing.x = -1.f;
				this->actor->facing.y = -1.f;
				this->actor->facing.z = 0.f;
			}
			else if (this->actor->moving_right) {

				this->actor->facing.x = 1.f;
				this->actor->facing.y = 0.f;
				this->actor->facing.z = 0.f;
			}
			else if (this->actor->moving_left) {
				this->actor->facing.x = -1.f;
				this->actor->facing.y = 0.f;
				this->actor->facing.z = 0.f;
			

			}
			else if (this->actor->moving_up) {

				this->actor->facing.x = 0.f;
				this->actor->facing.y = -1.f;
				this->actor->facing.z = 0.f;
			

			}
			else if (this->actor->moving_down) {
				this->actor->facing.x = 0.f;
				this->actor->facing.y = 1.f;
				this->actor->facing.z = 0.f;

			}
		}
		else {
			
		}
	
	this->actor->facing.normalize();
	this->actor->bound.min.z += this->actor->dz;
	this->actor->bound.max.z += this->actor->dz;
	if (this->actor->bound.min.z  > 0 && this->actor->jumping) {
		this->actor->bound.min.z = 0;
		this->actor->bound.max.z = actor->level;
		land();
	}
	if (this->actor->jumping && this->actor->bound.min.z < 0) {
		this->actor->dz += this->actor->gravity;

	}
	if (moving&&movable) {
		Moo::Vector3D deltaMove = this->actor->facing*this->actor->ms;
		this->actor->bound.min += deltaMove;
		this->actor->bound.max += deltaMove;
	}
	this->actor->bound.setCenter();
	sf::Vector2f scale = actor->shadow.getScale();
	float depthLength = actor->width*scale.y;
	this->actor->shadow.setPosition(actor->bound.cent.x-actor->width/2.f, actor->bound.max.y+actor->level- depthLength / 2.f);
	this->actor->shape.setPosition(this->actor->bound.cent.x - this->actor->width/2.f, actor->bound.min.y + actor->bound.min.z);
}

void CharacterMovingState::jump()
{
	std::cout << "Jumping" << std::endl;
	this->actor->dz = -10;
}
void CharacterMovingState::land() {
	std::cout << "Landing" << std::endl;
	this->actor->jumping = false;
	this->actor->dz = 0;
}

void CharacterMovingState::move() {

}
