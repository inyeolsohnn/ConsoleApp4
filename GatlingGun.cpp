#include "stdafx.h"
#include "GatlingGun.h"
#include "Actor.h"
#include "StartGameState.h"

GatlingGun::GatlingGun(std::vector<Status> statusInflicts, float duration, float cooldown, Actor* actor) : Active(statusInflicts, duration, cooldown, actor)
{
	this->skillname = "Gatling gun";
}


GatlingGun::~GatlingGun()
{
	std::cout << "Active Gatling gun destructor" << std::endl;
}

void GatlingGun::handleInput(sf::Event event)
{
}

void GatlingGun::execute(float dt)
{
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
		pPtr->setVelocity(10.f, 0.f, 0.f);
		pPtr->castedBy = castedBy;
		Moo::Vector3D min(this->castedBy->bound.cent.x - 1, this->castedBy->bound.cent.y - 1, this->castedBy->bound.cent.z - 1);
		Moo::Vector3D max(this->castedBy->bound.cent.x + 1, this->castedBy->bound.cent.y + 1, this->castedBy->bound.cent.z + 1);
		pPtr->bound = Moo::BoundingBox(min, max);
		pPtr->projectileBody->setPosition(pPtr->bound.cent.x, pPtr->bound.cent.y + pPtr->bound.cent.z);
		this->castedBy->flagForSpawn(pPtr, Actor::SPAWN);
		this->castedBy->getDamaged(0);
	
	firedCount++;
}
