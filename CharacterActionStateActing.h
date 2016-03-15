#pragma once
#include "CharacterActionState.h"
class CharacterActionStateActing :
	public CharacterActionState
{
public:
	enum ActiveState {CASTING, ACTIVATED, RECOVERING};
public:
	std::shared_ptr<Active> currentActive;
	ActiveState activeState;
	sf::Time timeSinceLastState;

public:
	CharacterActionStateActing(Actor* actor, std::shared_ptr<Active> active);
	virtual ~CharacterActionStateActing();
	void handleInput(sf::Event event);
	void update(float dt);
};

