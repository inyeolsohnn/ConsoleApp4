 #include "stdafx.h"
#include "CharacterActionStateActing.h"
#include "CharacterActionStateIdle.h"
#include "CharacterMovingState.h"

CharacterActionStateActing::CharacterActionStateActing(Actor* actor, std::shared_ptr<Active> active) : CharacterActionState(actor)
{
	this->currentActive = active;
	this->actionState = CharacterActionState::ActionState::ACTING;
	this->activeState = CASTING;
	this->timeSinceLastState = sf::milliseconds(0.0f);
	
}


CharacterActionStateActing::~CharacterActionStateActing()
{
	std::cout << "Action state acting destructor" << std::endl;
}

void CharacterActionStateActing::handleInput(sf::Event event)
{
	CharacterActionState::handleInput(event);
	this->currentActive->handleInput(event);
}

void CharacterActionStateActing::update(float dt)
{
	this->actor->moveState_->movable = currentActive->actorMovable;
	this->actor->moveState_->rotatable = currentActive->actorRotatable;

	this->currentActive->execute(dt);
	if (this->currentActive->elapsed >= this->currentActive->duration) {
		std::cout << "Ending active : "<<this->currentActive->skillname<<std::endl;
		this->actor->actionState_ = std::make_unique<CharacterActionStateIdle>(this->actor);
		this->currentActive->elapsed = sf::milliseconds(0.f);
		std::cout << "going in to action idle state" << std::endl;
		actor->moveState_->rotatable = true;
		actor->moveState_->movable = true;
	}
	
}
