#include "stdafx.h"
#include "CharacterStateRecovery.h"


CharacterStateRecovery::CharacterStateRecovery(Actor* actor) : CharacterMovingState(actor)
{
	this->charStateType = CharacterState::CharacterStateType::Move;
}


CharacterStateRecovery::~CharacterStateRecovery()
{
}

void CharacterStateRecovery::update(float dt)
{
	
}
void CharacterStateRecovery::handleInput(sf::Event event) {

}