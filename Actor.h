#ifndef ACTOR_H
#define ACTOR_H
#include <SFML/Graphics.hpp>
#include "Animation.h"
#include "AnimationManager.h"
#include "Active.h"
#include "Status.h"
#include "Damageable.h"
#include "Controllable.h"
#include "Physical.h"
class StartGameState;
class CharacterActionState;
class CharacterMovingState;

class Actor :  public Controllable
{
	
public:
	Actor();
	Actor(const unsigned int width, const unsigned int height, const unsigned int level, StartGameState* sgs, Moo::BoundingBox box);
	virtual ~Actor();
	int health;

	enum SpawnType{DESPAWN, SPAWN};
	float gravity;	
	std::unique_ptr<CharacterActionState> actionState_;
	std::unique_ptr<CharacterMovingState> moveState_;
	std::map<std::string, std::shared_ptr<Active>> skillMap;
	std::map<sf::Keyboard::Key, std::string> mapping;
	std::map<std::string, Status> statusMap;
	bool moving_down = false;
	bool moving_right = false;
	bool moving_up = false;
	bool moving_left = false;
	bool jumping = false;
	float controllable = 1.0f;
	sf::Sprite sprite;
	AnimationManager animMgr;
	sf::CircleShape shape;
	int width, height, level;
	void collide(Collidable* collidee);
	

	float dz;
	
	
	virtual void getDamaged(int x);
	virtual void draw(sf::RenderWindow& window, float dt);
	virtual void update(float dt);
	virtual void handleInput(sf::Event event);
	virtual void flagForSpawn(std::shared_ptr<Controllable> controlPtr, SpawnType spawnType);
	virtual void flagForSpawn(std::shared_ptr<Physical> physicalPtr, SpawnType spawnType);
	void removeStates();
	StartGameState* gameState; //the game actor belongs to
private:
	static void initializeSkillMap(std::string actorName, std::map<std::string, std::shared_ptr<Active>> & skillMap, Actor* actor);
	void initializeMapping();

	

};
#endif
