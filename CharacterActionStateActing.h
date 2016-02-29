#pragma once
#include "CharacterActionState.h"
class CharacterActionStateActing :
	public CharacterActionState
{
public:
	enum ActiveState {CASTING, ACTIVATED, RECOVERING};
	CharacterActionStateActing(Actor* actor, std::shared_ptr<Active> active);
	virtual ~CharacterActionStateActing();

	std::shared_ptr<Active> currentActive;
	ActiveState activeState;
	sf::Time timeSinceLastState;
	
	void handleInput(sf::Event event);
	void update(float dt);
};

