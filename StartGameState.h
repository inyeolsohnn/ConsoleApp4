#pragma once
#include "GameState.h"
#include "WorldMapGameState.h"
#include "Physical.h"
#include "Controllable.h"
#include "CollisionResolver.h"

#include "Octree.h"
class StartGameState :
	public GameState
{

private:
	sf::View view;
public:
	StartGameState(Game* game);
	virtual ~StartGameState();
	Moo::Vector3D min;
	Moo::Vector3D max;
	Moo::BoundingBox mainBox;
	Octree octree;
	CollisionResolver cr;
	std::vector<std::shared_ptr<Physical>> physicals;
	std::vector<std::shared_ptr<Controllable>> controllables;


	std::vector<std::shared_ptr<Physical>> physicalSpawnCache;
	std::vector<std::shared_ptr<Controllable>> controlSpawnCache;
	std::vector<std::shared_ptr<Physical>> physicalDespawnCache;
	std::vector<std::shared_ptr<Controllable>> controlDespawnCache;
	//Actor* actor;
	virtual void draw(const float dt);
	virtual void update(const float dt);
	virtual void handleInput();
private:
	void loadGame();
	

};

