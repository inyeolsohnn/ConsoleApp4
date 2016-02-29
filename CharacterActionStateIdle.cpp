#include "stdafx.h"
#include "CharacterActionStateIdle.h"
#include "CharacterActionStateActing.h"
#include <iostream>


CharacterActionStateIdle::CharacterActionStateIdle(Actor* actor) : CharacterActionState(actor)
{
	this->actionState = CharacterActionState::ActionState::ACTING;
	this->movable = true;
}


CharacterActionStateIdle::~CharacterActionStateIdle()
{
	std::cout << "Action state idle destructor" << std::endl;
}

void CharacterActionStateIdle::handleInput(sf::Event event)
{
	CharacterActionState::handleInput(event); 
}

void CharacterActionStateIdle::update(float dt)
{
	
}
