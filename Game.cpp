#include "stdafx.h"
#include "Game.h"
#include <iostream>
#include "GameState.h"

void Game::loadTextures()
{
	texmgr.loadTexture("background", "media/background.png");
	texmgr.loadTexture("dirt", "media/dirt.png");

}

void Game::loadTiles()
{
	Animation sa(0, 0, 1.0f);
	this->tileAtlas["dirt"] = Tile(100, 100, 0, texmgr.getRef("dirt"), { sa });

}

void Game::pushState(GameState * state)
{
	this->states.push(state);
}

void Game::popState()
{
	
	delete this->states.top();
	std::cout << "popState" << std::endl;

	this->states.pop();
}

void Game::changeState(GameState * state)
{
	if (!this->states.empty())
		delete this->states.top();
	pushState(state);
}

GameState * Game::peekState()
{
	if(this->states.empty()) return nullptr;
	return this->states.top();
}

Game::Game()
{
	this->loadTextures();
	this->loadTiles();
	this->tile = this->tileAtlas["dirt"];
	
	int width = this->tile.sprite.getGlobalBounds().width;
	int height = this->tile.sprite.getGlobalBounds().height;
	std::cout << width << std::endl;
	std::cout << height << std::endl;
	
	this->window.create(sf::VideoMode(800, 600), "God Complex");
	this->window.setKeyRepeatEnabled(false);
	std::cout << this->window.getSize().x << std::endl;
	std::cout << this->window.getSize().y / height << std::endl;
	tile.sprite.setScale(this->window.getSize().x/width, (this->window.getSize().y/height)/2);
	this->tile.sprite.setPosition(0.f, this->window.getSize().y/2);
	this->background.setTexture(texmgr.getRef("background"));
}


Game::~Game()
{	
	std::cout << "Game destructor" << std::endl;	
	while (!this->states.empty()) popState();

	std::cout << "Game desctructor complete" << std::endl;

}
