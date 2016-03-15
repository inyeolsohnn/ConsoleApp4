// God Complex.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include <chrono>
#include <thread>
#include "Game.h"
#include "GameState.h"
#include "StartGameState.h"
#include <time.h>
#include <iostream>
#include <SFML/System.hpp>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <direct.h>
#include "Vector3D.h"
#include "BoundingBox.h"


int main()
{
	
	Moo::Vector3D min1(1.f, 1.f, 1.f);
	Moo::Vector3D max1(3.f, 3.f, 3.f);
	Moo::BoundingBox box1(min1, max1);

	Moo::Vector3D min2(10.f, 10.f, 10.f);
	Moo::Vector3D max2(13.f, 12.f, 12.f);
	Moo::BoundingBox box2(min2, max2);
	std::cout << box1.contains(box2)<< std::endl;


	const int TICKS_PER_SECOND = 60;
	const int SKIP_TICKS = 1000 / TICKS_PER_SECOND;
	const int MAX_FRAMESKIP = 3;
	sf::Clock systemClock;
	float next_game_tick = systemClock.getElapsedTime().asMilliseconds();
	int loops;

	char full[_MAX_PATH];
	if (_fullpath(full, ".\\", _MAX_PATH) != NULL)
		printf("Full path is: %s\n", full);
	else
		printf("Invalid path\n");

	float lastUpdated = 0;

	Game game;
	game.pushState(new StartGameState(&game));
	while (game.window.isOpen()) {


		if (systemClock.getElapsedTime().asMilliseconds() >= next_game_tick) {

			float dt = systemClock.getElapsedTime().asMilliseconds() - lastUpdated;

			if (game.peekState() == nullptr) continue;
			game.peekState()->handleInput();
			game.peekState()->update(dt);

			game.peekState()->draw(dt);
			game.window.display();
			game.window.clear(sf::Color::Black);
			next_game_tick += SKIP_TICKS;

			lastUpdated = systemClock.getElapsedTime().asMilliseconds();


		}


	}

	return 0;
}

