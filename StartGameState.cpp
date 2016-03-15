#include "stdafx.h"
#include "StartGameState.h"
#include <iostream>



StartGameState::StartGameState(Game* game)
{
	this->game = game;
	sf::Vector2f pos = sf::Vector2f(this->game->window.getSize());
	this->view.setSize(pos);
	pos *= 0.5f;
	this->view.setCenter(pos);
	//this->actor =new Actor(100, 100, 0, &*this);
	Moo::Vector3D min1(40, 295, 0);
	Moo::Vector3D max1(60, 305, 80);
	Moo::BoundingBox box1(min1, max1);

	Moo::Vector3D min2(140, 295, 0);
	Moo::Vector3D max2(180, 345, 80);
	Moo::BoundingBox box2(min2, max2);
	std::shared_ptr<Actor> a1 = std::make_shared<Actor>(20, 10, 80, &*this, box1);  //id0

	std::shared_ptr<Actor> a2 = std::make_shared<Actor>(40, 50, 80, &*this, box2); //id1
	
	

	//this->controllables.push_back(a3);
	this->controllables.push_back(a1);
	this->controllables.push_back(a2);
	this->min = Moo::Vector3D(); 
	this->max = Moo::Vector3D(2000.f, 2000.f, 2000.f);
	this->mainBox = Moo::BoundingBox(min, max);
	this->octree = Octree(0, mainBox, nullptr, &(this->cr));
	a2->moving_right = false;
	a2->controllable = false;
	a2->shape.setFillColor(sf::Color::Red);
	
}

StartGameState::~StartGameState()
{
	
	//delete this->actor;

}

void StartGameState::draw(const float dt)
{
	std::vector<std::shared_ptr<Collidable>> renderVector;
	this->game->window.setView(this->view);
	this->game->window.clear(sf::Color::Black);
	this->game->window.draw(this->game->background);
	this->game->tile.draw(this->game->window, 0.0f);
	//actor->draw(this->game->window, 0.0f);
	auto controllableIt = this->controllables.begin();
	auto physicalIt = this->physicals.begin();
	for (; controllableIt != this->controllables.end(); controllableIt++) {
	//	(*controllableIt)->draw(this->game->window,dt);
		renderVector.push_back(*controllableIt);
	}
	for (; physicalIt != this->physicals.end(); physicalIt++) {
	//	(*physicalIt)->draw(this->game->window, dt);
		renderVector.push_back(*physicalIt);
	}

	std::sort(renderVector.begin(), renderVector.end(), [](const std::shared_ptr<Collidable>& a, const std::shared_ptr<Collidable>& b)->bool {
		return a->bound.cent.y < b->bound.cent.y;
	});
	for (auto rendIt = renderVector.begin(); rendIt != renderVector.end(); rendIt++) {
		(*rendIt)->drawShadow(this->game->window, dt);
	}
	for (auto rendIt = renderVector.begin(); rendIt != renderVector.end(); rendIt++) {
		(*rendIt)->draw(this->game->window, dt);
	}
	return;
}

void StartGameState::update(const float dt)
{

	auto controllableIt = this->controllables.begin();
	auto physicalIt = this->physicals.begin();
	
	//end collision test and resolution
	//Updating game
	

	
	while (controllableIt != this->controllables.end()) {
		if ((*controllableIt)->expired) {
			
			controllableIt = controllables.erase(controllableIt);
		
		}
		else {
			(*controllableIt)->update(dt);
			controllableIt++;
		}
	}
	
	while (physicalIt != this->physicals.end()) {
		if ((*physicalIt)->expired) {
			
			physicalIt = physicals.erase(physicalIt);
		
		}
		else {
			(*physicalIt)->update(dt);
			physicalIt++;
		}
	}
	
	auto physicalSpawnIt = this->physicalSpawnCache.begin();
	auto controllableSpawnIt = this->controlSpawnCache.begin();

	for (; physicalSpawnIt != this->physicalSpawnCache.end(); physicalSpawnIt++) {
		physicals.push_back(*physicalSpawnIt);
	
	}
	for (; controllableSpawnIt != this->controlSpawnCache.end(); controllableSpawnIt++) {
		controllables.push_back(*controllableSpawnIt);
	}
	auto physicalDespawnIt = this->physicalDespawnCache.begin();
	auto controllableDespawnIt = this->controlDespawnCache.begin();

	for (; physicalDespawnIt != this->physicalDespawnCache.end(); physicalDespawnIt++) {
		std::shared_ptr<Physical> currentShPointer = *physicalDespawnIt;
		std::vector<std::shared_ptr<Physical>>::iterator foundIt=std::find_if(physicals.begin(), physicals.end(), [&](std::shared_ptr<Physical>  p) {
				return &*p == &*currentShPointer;
		});
		if (foundIt != physicals.end()) {
			//forced despawn
			
		}
	}
	for (; controllableDespawnIt != this->controlDespawnCache.end(); controllableDespawnIt++) {
		controllables.push_back(*controllableSpawnIt);
	}
	 //end game update

	
	octree.clear();
	physicalIt = physicals.begin();
	controllableIt = controllables.begin();


	while (physicalIt != physicals.end()) {
		octree.insert(std::static_pointer_cast<Collidable>(*physicalIt));
		physicalIt++;
	}
	while (controllableIt != controllables.end()) {
		octree.insert(std::static_pointer_cast<Collidable>(*controllableIt));
		controllableIt++;
	}

	octree.checkCollision();

	//clearing caches//
	physicalSpawnCache.clear();
	controlSpawnCache.clear();
	physicalDespawnCache.clear();
	controlDespawnCache.clear();
	//end clearing caches//
}

void StartGameState::handleInput()
{
	sf::Event event;

	while (this->game->window.pollEvent(event)) {
		switch (event.type) {
		case sf::Event::Closed:{
			game->window.close();
			break;
			}
		case sf::Event::Resized:
		{
			this->view.setSize(event.size.width, event.size.height);
			this->view.setCenter(event.size.width / 2, event.size.height / 2);
			this->game->background.setPosition(this->game->window.mapPixelToCoords(sf::Vector2i(0, 0)));
			this->game->background.setScale(
				float(event.size.width) / float(this->game->background.getTexture()->getSize().x),
				float(event.size.height) / float(this->game->background.getTexture()->getSize().y));
			break;
		}
				
		default: break;
		}
	//	this->actor->handleInput( event);
		auto controllableIt = this->controllables.begin();
		for (; controllableIt != this->controllables.end(); controllableIt++) {
			(*controllableIt)->handleInput(event);
		}
	}
	
}

void StartGameState::loadGame()
{
	this->game->states.push(new WorldMapGameState(this->game));
}
