#include "stdafx.h"
#include "Actor.h"
#include "CharacterActionState.h"
#include "CharacterActionStateIdle.h"
#include "CharacterMovingState.h"
#include "CharacterStateRecovery.h"
#include "StartGameState.h"
#include "Active.h"
#include "GatlingGun.h"
#include <iostream>


Actor::Actor(const unsigned int width, const unsigned int height, const unsigned int level, StartGameState* sgs, Moo::BoundingBox box)
{
	shape = sf::CircleShape(10.f);
	shape.setFillColor(sf::Color::Green);
	this->gameState = sgs;
	this->width = width;
	this->height = height;
	this->level = level;
	
	this->gravity = 0.3f;
	this->dz = 0;

	bound = box;
	shape.setPosition(bound.cent.x-10, bound.cent.y+bound.cent.z-10);
	
	this->moveState_ = std::make_unique<CharacterMovingState>(&*this);
	this->health = 100;
	this->actionState_ = std::make_unique<CharacterActionStateIdle>(&*this);
	initializeSkillMap("firstChar", this->skillMap, &*this);
	initializeMapping();
		
}

Actor::Actor() {

}

Actor::~Actor()
{
	std::cout << "Actor deconstructor" << std::endl;
}

void Actor::draw(sf::RenderWindow & window, float dt)
{
	window.draw(this->shape);
}

void Actor::update(float dt)
{
	if (controllable == 0.f) {
		this->moving_up = false;
		this->moving_left = false;
		this->moving_down = false;
		this->moving_right = false;
	}
	if (this->moveState_ != nullptr) {
		this->moveState_->update(dt);
	}

	if (this->actionState_ != nullptr) {
		this->actionState_->update(dt);
	}

	for (auto& it = this->statusMap.begin(); it != this->statusMap.end();) {
		it->second.update(dt, &*this);
		if (it->second.elapsed.asMilliseconds() >= sf::milliseconds(it->second.statusduration).asMilliseconds()) {
			std::cout << "ending after "<<it->second.elapsed.asMilliseconds() << std::endl;
			it->second.endStatus(&*this);
			it = statusMap.erase(it);
		}
		else {
			++it;
		}
	}
	

	if (this->health <= 0) {
		this->expired = true;
	}
	

}

void Actor::handleInput( sf::Event event)
{
	if (this->moveState_ != nullptr&&this->actionState_ != nullptr) {
		if (controllable) {
			this->moveState_->handleInput(event);
			this->actionState_->handleInput(event);
		}
	}
}
void Actor::flagForSpawn(std::shared_ptr<Controllable> controllableObject, SpawnType spawnType)
{
	if (spawnType == SPAWN) {
		this->gameState->controlSpawnCache.push_back(controllableObject);
	}
	else if (spawnType == DESPAWN) {
		this->gameState->controlDespawnCache.push_back(controllableObject);
	}
}
void Actor::flagForSpawn(std::shared_ptr<Physical> physicalObject, SpawnType spawnType) {
	if (spawnType == SPAWN) {
		this->gameState->physicalSpawnCache.push_back(physicalObject);
	}
	else if (spawnType == DESPAWN) {
		this->gameState->physicalSpawnCache.push_back(physicalObject);
	}

}
void Actor::removeStates()
{
	this->actionState_=nullptr;
	this->moveState_=nullptr;
}
 void Actor::initializeSkillMap(std::string actorName, std::map<std::string, std::shared_ptr<Active>>& skillMap, Actor* actor)
{
	std::vector<Status> ggVec;
	float duration(5000);
	float cooldown(3000);
	std::shared_ptr<Active> actPtr= std::make_shared<GatlingGun>(ggVec, duration, cooldown, actor);

	skillMap["Gatling gun"] = actPtr;
	

}
 void Actor::initializeMapping() {
	 this->mapping[sf::Keyboard::A] = "Gatling gun";
 }

 void Actor::collide(Collidable* collidee) {

 }

 void Actor::getDamaged(int damage) {
	 this->health -= damage;
 }


