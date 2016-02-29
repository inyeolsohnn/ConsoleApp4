#pragma once
#include"Collidable.h"
#include <vector>
#include "BoundingBox.h"
#include"CollisionResolver.h"
#include <memory>
class Octree
{
public:
	//const&deconst//
	Octree();
	Octree(int pLevel, Moo::BoundingBox boxBounds, Octree* parent, CollisionResolver* cr):level(pLevel), bounds(boxBounds), parent(parent), cr(cr) {
	
	}
	~Octree();
	//const& deconst//

	//const variables//
	  unsigned int MIN_SIZE = 1;
	  unsigned int MAX_OBJECTS = 10;
	  unsigned int MAX_LEVELS = 10;
	//constvariables

	//members
	int level;
	Moo::BoundingBox bounds;
	std::vector<std::shared_ptr<Collidable>> objects;
	std::shared_ptr<Octree> childNode[8];
	Octree* parent; //nullptr for root
	CollisionResolver* cr;
	//members

	//START: Method declarations

	void clear();
	std::vector<std::shared_ptr<Collidable>> retrieve(std::vector <std::shared_ptr<Collidable>>& resultList,
		const Collidable& collidable);
	void insert(std::shared_ptr<Collidable >collidable);
	void checkCollision();

private:
	void split();
	std::vector<int> getIndexes(const std::shared_ptr<Collidable >& collidable) const;




	

};

