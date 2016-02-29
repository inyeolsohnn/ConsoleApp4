#include "stdafx.h"
#include "Active.h"


Active::Active()
{
}

Active::Active(std::vector<Status> inflictingStatusVec, float duration, float cooldown, Actor* actor) 
	: statusVec(inflictingStatusVec), duration(sf::milliseconds(duration)), cooldown(sf::milliseconds(cooldown)), castedBy(actor)
{
	this->elapsed = sf::milliseconds(0.f);
}


Active::~Active()
{
	std::cout << "Active base destructor" << std::endl;
}


