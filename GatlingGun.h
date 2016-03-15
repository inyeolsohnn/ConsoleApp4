#pragma once
#include "Active.h"
class GatlingGun :
	public Active
{
public:
	GatlingGun(std::vector<Status> statusInflicts, float duration, float cooldown, Actor* actor);
	virtual ~GatlingGun();
	void handleInput(sf::Event event);
	void execute(float dt);
	bool checkCondition(Actor* actor);
private:
	sf::Time rate;
	Moo::Vector3D direction;
	int firedCount=0;
	void fire();
};

