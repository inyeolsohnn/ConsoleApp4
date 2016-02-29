#include "stdafx.h"
#include "Octree.h"
#include <iostream>

Octree::Octree()
{

	//initializing array with null ptr
	for (int i = 0; i < 8; i++) {
		childNode[i] = nullptr;
	}
}


Octree::~Octree()
{

}

void Octree::clear()
{
	
	this->objects.clear();	
	for (int i = 0; i < 8; i++) {
		if (childNode[i] != nullptr) {
			childNode[i]->clear();
			childNode[i] = nullptr;
		}
	}	
	this->parent = nullptr;
	
}

std::vector<std::shared_ptr<Collidable>> Octree::retrieve(std::vector<std::shared_ptr<Collidable>>& resultList, const Collidable & collidable)
{
	return std::vector<std::shared_ptr<Collidable>>();
}

void Octree::split()
{
	float subX = bounds.cent.x;
	float subY = bounds.cent.y;
	float subZ = bounds.cent.z;

	Moo::Vector3D halfD = bounds.cent - bounds.min;
	int nextLevel = level + 1;
	//lower layer cells(0-3)
	Moo::BoundingBox box0(bounds.min, bounds.cent);
	std::shared_ptr<Octree> oct0 = std::make_shared<Octree>(nextLevel, box0, &*this, this->cr);

	Moo::Vector3D box1Min(bounds.min.x, bounds.min.y, bounds.cent.z);
	Moo::Vector3D box1Max = box1Min + halfD;
	Moo::BoundingBox box1(box1Min, box1Max);
	std::shared_ptr<Octree> oct1 = std::make_shared<Octree>(nextLevel, box1, &*this, this->cr);

	Moo::Vector3D box2Min(bounds.cent.x, bounds.min.y, bounds.cent.z);
	Moo::Vector3D box2Max = box2Min + halfD;
	Moo::BoundingBox box2(box2Min, box2Max);
	std::shared_ptr<Octree> oct2 = std::make_shared<Octree>(nextLevel, box2, &*this, this->cr);

	Moo::Vector3D box3Min(bounds.cent.x, bounds.min.y, bounds.min.z);
	Moo::Vector3D box3Max = box3Min + halfD;
	Moo::BoundingBox box3(box3Min, box3Max);
	std::shared_ptr<Octree> oct3 = std::make_shared<Octree>(nextLevel, box3, &*this, this->cr);

	//upper layer cells(4-7)
	Moo::Vector3D box4Min(bounds.min.x, bounds.cent.y, bounds.min.z);
	Moo::Vector3D box4Max = box4Min + halfD;
	Moo::BoundingBox box4(box4Min, box4Max);
	std::shared_ptr<Octree> oct4 = std::make_shared<Octree>(nextLevel, box4, &*this, this->cr);

	Moo::Vector3D box5Min(bounds.min.x, bounds.cent.y, bounds.cent.z);
	Moo::Vector3D box5Max = box5Min + halfD;
	Moo::BoundingBox box5(box5Min, box5Max);
	std::shared_ptr<Octree> oct5 = std::make_shared<Octree>(nextLevel, box5, &*this, this->cr);

	Moo::Vector3D box6Min = bounds.cent;
	Moo::Vector3D box6Max = bounds.max;
	Moo::BoundingBox box6(box6Min, box6Max);
	std::shared_ptr<Octree> oct6 = std::make_shared<Octree>(nextLevel, box6, &*this, this->cr);

	Moo::Vector3D box7Min(bounds.cent.x, bounds.cent.y, bounds.min.z);
	Moo::Vector3D box7Max = box7Min + bounds.cent;
	Moo::BoundingBox box7(box7Min, box7Max);
	std::shared_ptr<Octree> oct7 = std::make_shared<Octree>(nextLevel, box7, &*this, this->cr);

	childNode[0] = oct0;
	childNode[1] = oct1;
	childNode[2] = oct2;
	childNode[3] = oct3;
	childNode[4] = oct4;
	childNode[5] = oct5;
	childNode[6] = oct6;
	childNode[7] = oct7;
	
}

std::vector<int> Octree::getIndexes(const std::shared_ptr<Collidable >& collidable) const
{

	std::vector<int> indexes;
	for (int i = 0; i < 8; i++) {
		Moo::ContainmentType ct= childNode[i]->bounds.contains(collidable->bound);
		if ( ct == Moo::ContainmentType::Intersect) {
			indexes.push_back(i);
		}
		else if (ct == Moo::ContainmentType::Contain) {
			indexes.push_back(i);
			break;
		}
	}
	return indexes;
}

void Octree::insert(std::shared_ptr<Collidable > collidable)
{
	if (childNode[0] != nullptr) { //child node exists. Recurse into children
		std::vector<int> indexes = getIndexes(collidable);
		for (auto indexIt =indexes.begin(); indexIt!=indexes.end(); indexIt++) {
			childNode[*indexIt]->insert(collidable);
		}
	}
	else {
		//arrived at leaf
		
		
		this->objects.push_back(collidable);

		if (this->objects.size() > MAX_OBJECTS && level < MAX_LEVELS) { //check for leave
			split();
			
			auto objectsIt = objects.begin();
			for (; objectsIt != objects.end(); objectsIt++) {
				std::vector<int> indexList = getIndexes(*objectsIt);
				for (auto indexIt = indexList.begin(); indexIt != indexList.end(); indexIt++) {
					childNode[*indexIt]->insert(*objectsIt);
				}
			}
			objects.clear();
		}
	}
}

void Octree::checkCollision()
{
	
	if (objects.size() != 0) {
		for (int i = 0; i < this->objects.size() - 1; i++) {
			for (int j = i + 1; j < this->objects.size(); j++) {
				//check collision between i and j
				if (objects.at(i)->bound.contains(objects.at(j)->bound)!=Moo::ContainmentType::Disjoint) {
					objects.at(i)->collide(&*objects.at(j));
					objects.at(j)->collide(&*objects.at(i));
				}
			}
		}
	}
	if (childNode[0] != nullptr) {
		for (int i = 0; i < 8; i++) {
			childNode[0]->checkCollision();
		}
	}


	
}
