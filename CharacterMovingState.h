#pragma once
#include "CharacterState.h"
class CharacterMovingState : public CharacterState
{
public:
	
	CharacterMovingState(Actor* actor);
	virtual ~CharacterMovingState(){ std::cout << "Moving state destructor" << std::endl; }

	void handleInput(sf::Event event);
	void update(float dt);
private: 
	void jump();
	void land();
};

