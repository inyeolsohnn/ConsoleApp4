#pragma once
#include"Actor.h"
class CharacterState
{
public:
	CharacterState(Actor* actor);
	virtual ~CharacterState();
	enum CharacterStateType {Action, Move};
	CharacterStateType charStateType;
	Actor* actor;

	virtual void update(float dt)=0;
	virtual void handleInput(sf::Event event)=0;
};

