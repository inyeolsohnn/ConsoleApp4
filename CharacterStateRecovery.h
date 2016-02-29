#pragma once

#include "CharacterMovingState.h"
class CharacterStateRecovery : public CharacterMovingState
{
public:
	bool changed;
	CharacterStateRecovery(Actor* actor);
	~CharacterStateRecovery();
	void update(float dt);
	void handleInput(sf::Event event);
};

