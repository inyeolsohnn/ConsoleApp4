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
#include <math.h>

int Actor::actorCounter = 0;
Actor::Actor(const unsigned int width, const unsigned int height, const unsigned int level, StartGameState* sgs, Moo::BoundingBox box):Controllable(box) //x, y, z
{
	shape = sf::RectangleShape(sf::Vector2f(width, bound.max.y-bound.min.y+level));
	shadow = sf::CircleShape(width/2.f);
	shadow.setFillColor(sf::Color::Black);
	shadow.setScale(1, 1+height/width);
	shape.setFillColor(sf::Color::Green);
	this->gameState = sgs;
	this->width = width;
	this->height = height;
	this->level = level;
	facing = Moo::Vector3D(1.f, -1.f, 0.f);
	this->gravity = 0.3f;
	this->dz = 0;
	float shadowDepth;
	sf::Vector2f scale =shadow.getScale();
	float depthLength = width*scale.y;
	shape.setPosition(bound.cent.x-width/2.f, bound.min.y+bound.min.z);
	shadow.setPosition(bound.cent.x-width/2.f, bound.max.y+level-depthLength/2.f);
	this->moveState_ = std::make_unique<CharacterMovingState>(&*this);
	this->health = 100000;
	this->actionState_ = std::make_unique<CharacterActionStateIdle>(&*this);
	initializeSkillMap("firstChar", this->skillMap, &*this);
	initializeMapping();
	actorId = actorCounter++;
		
}

Actor::Actor(const Actor & src): Controllable(src.bound), gameState(src.gameState),gravity(src.gravity),health(src.health),facing(facing), moving_down(src.moving_down), 
	moving_right(src.moving_right), moving_up(src.moving_up), moving_left(src.moving_left), jumping(src.jumping), ms(src.ms), controllable(src.controllable), 
	sprite(src.sprite), shadow(src.shadow), animMgr(src.animMgr), shape(src.shape), width(src.width), height(src.height), level(src.level), dz(src.dz), skillMap(src.skillMap), mapping(src.mapping), statusMap(src.statusMap)
{
	std::cout << "Actor copy ctor" << std::endl;
	actionState_ = std::make_unique<CharacterActionStateIdle>(&*this);
	moveState_ = std::make_unique<CharacterMovingState>(&*this);
	actorId = actorCounter++;
	std::map<std::string, std::shared_ptr<Active>>::iterator skillIt = skillMap.begin();
	while (skillIt != skillMap.end()) {
		skillIt->second->castedBy = &*this;
		++skillIt;
	}
}



Actor::Actor(Actor&& src):Controllable(src.bound), gameState(src.gameState), gravity(src.gravity), health(src.health), facing(facing), moving_down(src.moving_down),
moving_right(src.moving_right), moving_up(src.moving_up), moving_left(src.moving_left), jumping(src.jumping), ms(src.ms), controllable(src.controllable),
sprite(src.sprite), shadow(src.shadow), animMgr(src.animMgr), shape(src.shape), width(src.width), height(src.height), level(src.level), dz(src.dz), skillMap(std::move(src.skillMap)), 
mapping(std::move(src.mapping)), statusMap(std::move(statusMap))
{
	
	std::cout << "Actor move ctor" << std::endl;
	actionState_ = std::move(src.actionState_);
	actionState_->actor = &*this;	
	moveState_ = std::move(src.moveState_);
	moveState_->actor = &*this;
	std::map<std::string, std::shared_ptr<Active>>::iterator skillIt = skillMap.begin();
	while (skillIt != skillMap.end()) {
		skillIt->second->castedBy = &*this;
		++skillIt;
	}
	std::cout << "Skill map after move : " << std::endl;
	std::map<std::string, std::shared_ptr<Active>>::iterator srcIt = src.skillMap.begin();
	int i = 0;
	while (srcIt != src.skillMap.end()) {
		std::cout << srcIt->first << std::endl;
		++i;
	}
	std::cout << "Skill map count : " << i << std::endl;
	actorId = src.actorId;
	src.actorId = -1;
}
Actor::Actor() {

}

Actor::~Actor()
{
	std::cout << "Actor deconstructor. Id : "<<actorId << std::endl;
}

void Actor::draw(sf::RenderWindow & window, float dt)
{
	
	window.draw(this->shape);
	
}

void Actor::update(float dt)
{

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
void Actor::drawShadow(sf::RenderWindow & window, float dt)
{
	window.draw(this->shadow);
}
void Actor::removeStates()
{
	this->actionState_=nullptr;
	this->moveState_=nullptr;
}
 void Actor::initializeSkillMap(std::string actorName, std::map<std::string, std::shared_ptr<Active>>& skillMap, Actor* actor)
{
	std::vector<Status> ggVec;
	float duration(2000);
	float cooldown(3000);
	std::shared_ptr<Active> actPtr= std::make_shared<GatlingGun>(ggVec, duration, cooldown, actor);

	skillMap["Gatling gun"] = actPtr;
	

}
 void Actor::initializeMapping() {
	 this->mapping[sf::Keyboard::A] = "Gatling gun";
 }

 void Actor::collide(Collidable* collidee) {
	 //actor-actor collision
	 if (Actor* ac=dynamic_cast<Actor*>(collidee)) {
		 std::cout << "Actor ID: " << this->actorId << "Collided with ID: " << ac->actorId << std::endl;
		 bool moving = moving_down||moving_left||moving_up||moving_right||jumping;
		
		if (moving) {
			Moo::Vector3D delta = ac->bound.cent+bound.cent*-1.0f;			
			delta.z = 0.f;
			
			/*
			
		
			
			delta.normalize();
			*/

			delta *= -1.0f;
			delta.normalize();
			bound.translate(delta);
			
		 }		 
	 }
 }

 void Actor::getDamaged(int damage) {
	 this->health -= damage;
 }


