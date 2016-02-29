#pragma once
#include <stdio.h>
#include <iostream>
#include <vector>
#include <map>
#include <SFML/System.hpp>

class Actor;
class Status
{
public:
	enum ConditionType { FALLING, ALL, NORMAL }; //e.g Falling: effect applies only when the char is falling
	enum TargetStatistics { ACTOR_DZ, ACTOR_X, ACTOR_CONTROL };
	enum TargetOperator { MULTIPLICATIVE, ADDITIVE, SET };
	enum PostStatus {ROLLBACK, NONE};
	enum Target { TARGET, SELF };
	enum SkillType { ACTIVE, PASSIVE };
	struct Effecter {
		float apply(float statVal, float appliedVal, TargetOperator operationtype) {
			float result;
			if (operationtype == MULTIPLICATIVE) {				
				result = statVal*appliedVal;
			}
			else if (operationtype == ADDITIVE) {
				result = statVal + appliedVal;
			}
			else if (operationtype == SET) {
				result = appliedVal;
			}
			return result;
		}
	};
	float valueOperand;
	std::string statusName;
	float range;	
	float statusduration;
	TargetStatistics statOperand;
	TargetOperator tOperator;
	ConditionType statusCondition;
	std::vector<ConditionType> requiredConditions;
	std::vector<ConditionType> endingCondition;
	PostStatus postStatus;
	sf::Time elapsed;
	Effecter effecter;
	float initialValue;

	Status() {};
	Status(TargetStatistics ts, TargetOperator to, float vo, std::string statusName, float range, float statusduration, ConditionType condition, PostStatus post);
	~Status();
	void effect(Actor* actor);
	void update(float dt, Actor* actor);
	void endStatus(Actor* actor);
	float* getStatusVar(Actor* actor);
private:
	bool checkCondition(Actor* actor);
	
};

