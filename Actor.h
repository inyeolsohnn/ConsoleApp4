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
	enum SpawnType { DESPAWN, SPAWN };
	static int actorCounter;

public:
	StartGameState* gameState;	
	float gravity;
	int health;
	std::unique_ptr<CharacterActionState> actionState_;
	std::unique_ptr<CharacterMovingState> moveState_;
	std::map<std::string, std::shared_ptr<Active>> skillMap;
	std::map<sf::Keyboard::Key, std::string> mapping;
	std::map<std::string, Status> statusMap;
	Moo::Vector3D facing;
	bool moving_down = false;
	bool moving_right = false;
	bool moving_up = false;
	bool moving_left = false;
	bool jumping = false;
	float ms = 1.f;
	float controllable = 1.0f;
	sf::Sprite sprite;
	AnimationManager animMgr;
	sf::RectangleShape shape;
	sf::CircleShape shadow;
	int width, height, level;
	float dz;
	
	int actorId;
public:
	Actor(Actor && src);
	Actor();
	Actor(const unsigned int width, const unsigned int height, const unsigned int level, StartGameState* sgs, Moo::BoundingBox box);
	Actor(const Actor& src);
	virtual ~Actor();
	void collide(Collidable* collidee);	
	virtual void getDamaged(int x);
	virtual void draw(sf::RenderWindow& window, float dt);
	virtual void update(float dt);
	virtual void handleInput(sf::Event event);
	virtual void flagForSpawn(std::shared_ptr<Controllable> controlPtr, SpawnType spawnType);
	virtual void flagForSpawn(std::shared_ptr<Physical> physicalPtr, SpawnType spawnType);
	virtual void drawShadow(sf::RenderWindow& window, float dt);
	void removeStates();
	//the game actor belongs to
private:
	static void initializeSkillMap(std::string actorName, std::map<std::string, std::shared_ptr<Active>> & skillMap, Actor* actor);
	void initializeMapping();

	

};
#endif
