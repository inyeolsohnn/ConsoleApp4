#include "stdafx.h"
#include "GatlingGun.h"
#include "Actor.h"
#include "StartGameState.h"
#include "CharacterActionStateActing.h"
#include "CharacterMovingState.h"

GatlingGun::GatlingGun(std::vector<Status> statusInflicts, float duration, float cooldown, Actor* actor) : Active(statusInflicts, duration, cooldown, actor)
{
	this->skillname = "Gatling gun";
	this->direction = actor->facing;
	this->actorCtrl = false;
	this->actorMovable = false;
	this->actorRotatable = false;
}


GatlingGun::~GatlingGun()
{
	std::cout << "Active Gatling gun destructor" << std::endl;
}

void GatlingGun::handleInput(sf::Event event)
{
	switch (event.type) {
	case sf::Event::KeyPressed:
	{
		
		if (event.key.code == sf::Keyboard::Z) {
			std::cout << "gatling gun z" << std::endl;
			this->direction.z = -0.2f;
		}
		if (event.key.code == sf::Keyboard::LControl) {
			std::cout << "gatling gun lctrl" << std::endl;
			this->direction.z = 0.f;
		}
		break;
	}
	
	default:
		break;
	}
}

void GatlingGun::execute(float dt)
{
	if (this->elapsed.asMilliseconds ()== 0.f) {
		std::cout << "First time" << std::endl;
		this->direction = castedBy->facing;
	}
	
	this->elapsed += sf::milliseconds(dt);	
	if (elapsed >= sf::milliseconds(480.f)) {
		this->rate += sf::milliseconds(dt);
		if (this->rate >= sf::milliseconds(200.f)) {
			this->rate = sf::milliseconds(0.f);
			fire();
			std::cout << this->castedBy->gameState->physicals.size() << std::endl;
			std::cout << this->castedBy->gameState->physicalSpawnCache.size() << std::endl;
		}
		//start firing
		//fire at every 200ms
	}
	
}
bool GatlingGun::checkCondition(Actor* actor) {
	return true;
}
void GatlingGun::fire() {

	
	
		std::cout << "bullet Fired : " << firedCount << std::endl;
		std::shared_ptr<Projectile> pPtr = std::make_shared<Projectile>();
		pPtr->projectileBody = std::make_unique<sf::CircleShape>(2.f);
		pPtr->dmg = 10;
		pPtr->projectileBody->setFillColor(sf::Color::Yellow);
		direction.normalize();
		float vel( 5.f);
		Moo::Vector3D directionalVel = direction*vel;
		pPtr->setVelocity(directionalVel.x, directionalVel.y, directionalVel.z);
		pPtr->castedBy = castedBy;
		Moo::Vector3D min(this->castedBy->bound.cent.x - 1, this->castedBy->bound.cent.y - 1, this->castedBy->bound.cent.z - 1);
		Moo::Vector3D max(this->castedBy->bound.cent.x + 1, this->castedBy->bound.cent.y + 1, this->castedBy->bound.cent.z + 1);
		pPtr->bound = Moo::BoundingBox(min, max);
		pPtr->projectileBody->setPosition(pPtr->bound.cent.x, pPtr->bound.cent.y + pPtr->bound.cent.z-this->castedBy->width);
		this->castedBy->flagForSpawn(pPtr, Actor::SPAWN);
		
	
	firedCount++;
}
