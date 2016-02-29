#pragma once
#include "CharacterActionState.h"
class CharacterActionStateIdle : public CharacterActionState
{
public:
	CharacterActionStateIdle(Actor* actor);
 	virtual ~CharacterActionStateIdle();
	void handleInput(sf::Event event);
	void update(float dt);
};

