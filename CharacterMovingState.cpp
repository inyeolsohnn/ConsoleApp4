#include "stdafx.h"
#include "CharacterMovingState.h"
#include "CharacterActionState.h"
#include <iostream>




CharacterMovingState::CharacterMovingState(Actor * actor):CharacterState(actor)
{
	this->charStateType = CharacterState::CharacterStateType::Move;	
}



void CharacterMovingState::handleInput(sf::Event event)
{
	switch (event.type) {
	case sf::Event::KeyPressed:
	{
		
		if (event.key.code == sf::Keyboard::Right) {
			std::cout << "right" << std::endl;
			this->actor->moving_right = true;
			std::cout << this->actor->moving_right << std::endl;
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
			std::cout << "Jump key pressed" << std::endl;
			this->actor->jumping = true;
			jump();
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
	if (this->actor->actionState_->movable) {
		if (this->actor->moving_right&&this->actor->moving_down) {
			this->actor->bound.min.x += 0.5;
			this->actor->bound.min.y += 0.5;
			this->actor->bound.max.x += 0.5;
			this->actor->bound.max.y += 0.5;
		}
		else if (this->actor->moving_right&&this->actor->moving_up) {		
			this->actor->bound.min.x += 0.5;
			this->actor->bound.min.y -= 0.5;
			this->actor->bound.max.x -= 0.5;
			this->actor->bound.max.y -= 0.5;
		}
		else if (this->actor->moving_left&&this->actor->moving_down) {		
			this->actor->bound.min.x -= 0.5;
			this->actor->bound.min.y += 0.5;
			this->actor->bound.max.x -= 0.5;
			this->actor->bound.max.y += 0.5;
		}
		else if (this->actor->moving_left&&this->actor->moving_up) {
			this->actor->bound.min.x -= 0.5;
			this->actor->bound.min.y -= 0.5;
			this->actor->bound.max.x -= 0.5;
			this->actor->bound.max.y -= 0.5;
		}
		else if (this->actor->moving_right) {

			this->actor->bound.min.x += 1;
		
			this->actor->bound.max.x += 1;
			
		}
		else if (this->actor->moving_left) {
			this->actor->bound.min.x -= 1;

			this->actor->bound.max.x -= 1;
		}
		else if (this->actor->moving_up) {
			this->actor->bound.min.y -= 1;

			this->actor->bound.max.y -= 1;
		}
		else if (this->actor->moving_down) {
			this->actor->bound.min.y += 1;

			this->actor->bound.max.y += 1;
		}
	}
	this->actor->bound.min.z += this->actor->dz;

	this->actor->bound.max.z += this->actor->dz;
	if (this->actor->bound.min.z  > 0 && this->actor->jumping) {
		this->actor->bound.min.z =0;
		this->actor->bound.max.z = 0;
		land();
	}
	if (this->actor->jumping && this->actor->bound.min.z < 0) {
		this->actor->dz += this->actor->gravity;

	}
	this->actor->bound.setCenter();
	this->actor->shape.setPosition(this->actor->bound.cent.x-10, this->actor->bound.cent.y + this->actor->bound.cent.z-10);

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
