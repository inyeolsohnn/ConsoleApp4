#pragma once
#include "CharacterState.h"
#include "Active.h"
#include "Actor.h"

class CharacterActionState : public CharacterState 
{
public:
	CharacterActionState(Actor* actor);
	virtual ~CharacterActionState();
	enum ActionState { IDLE, ACTING };
	
	ActionState actionState;

	virtual void update(float dt) ;
	virtual void handleInput(sf::Event event) ;
};

