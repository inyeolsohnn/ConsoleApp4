#pragma once
#include <vector>
#include <map>
#include "Status.h"
#include "Projectile.h"
#include <memory>
class Active
{
public:
	//method definition
	std::vector<Status> statusVec;
	std::string skillname;
	sf::Time duration;
	sf::Time cooldown;
	sf::Time elapsed;
	Actor* castedBy;
	bool started = false;
	bool ended = false;

	//method declaration
	Active();
	Active(std::vector<Status> statusInflicts, float duration, float cooldown, Actor* actor);
	virtual ~Active();
	
	virtual void handleInput(sf::Event event)=0;
	virtual void execute(float dt)=0;
	virtual bool checkCondition(Actor* actor)=0;
};

