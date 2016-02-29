#include "stdafx.h"
#include "Status.h"
#include "Actor.h"


void Status::effect(Actor* actor)
{
	this->elapsed = sf::milliseconds(0.0f);
	actor->statusMap[this->statusName] = *this;
	if (this->postStatus == ROLLBACK) {
		float* valp = getStatusVar(actor);
		this->initialValue=float (*valp);
	}
}

void Status::update(float dt, Actor* actor)
{
	
	
}
void Status::endStatus(Actor* actor) {

}

bool Status::checkCondition(Actor* actor)
{ 
	if (this->statusCondition == ALL) {
		return true;
	}
	else if(this->statusCondition==FALLING){
		if(actor->dz>0&&actor->jumping )
			return true;
		else {
			return false;
		}
	}
	else if (this->statusCondition == NORMAL) {
		if (actor->jumping == false)
			return true;
		else {
			return false;
		}
	}
	else {
		return false;
	}
}

float* Status::getStatusVar(Actor* actor) {
	float* valp=nullptr;

	return valp;
}


Status::Status(TargetStatistics ts, TargetOperator to, float vo, std::string statusName, float range, float statusduration, ConditionType condition, PostStatus ps)
	:statOperand(ts), tOperator(to), valueOperand(vo), statusName(statusName), range(range), statusduration(statusduration), statusCondition(condition), postStatus(ps)
{
	

}


Status::~Status()
{
}
