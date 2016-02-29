#include "stdafx.h"
#include "CharacterActionState.h"
#include "CharacterActionStateActing.h"
#include "CharacterActionStateIdle.h"


CharacterActionState::CharacterActionState(Actor* actor) : CharacterState(actor)
{
	this->charStateType = CharacterState::CharacterStateType::Action;	
}


CharacterActionState::~CharacterActionState()
{
	std::cout << "I'M DESTROYED : BASE ACTION" << std::endl;
}

void CharacterActionState::update(float dt)
{
}

void CharacterActionState::handleInput(sf::Event event)
{
	std::shared_ptr<Active> active=nullptr;
	switch (event.type) {
	case sf::Event::KeyPressed:
	{

		if (event.key.code == sf::Keyboard::A) {
			if (this->actor->mapping.find(sf::Keyboard::A)  != this->actor->mapping.end()) {
				std::cout << "Skill found" << std::endl;
				active = (this->actor->skillMap[this->actor->mapping[sf::Keyboard::A]]);
				std::cout << "Skill Name : " << active->skillname << std::endl;
			}
		}

		break;
	}

	default:
		break;
	}
	if (active != nullptr) {
		this->actor->actionState_ = std::make_unique<CharacterActionStateActing>(this->actor, active);
		std::cout << "going in to acting state" << std::endl;
		
	}
}
