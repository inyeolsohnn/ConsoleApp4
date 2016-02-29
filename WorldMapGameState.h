#ifndef WORLD_MAP_GAME_STATE
#define WORLD_MAP_GAME_STATE

#include <SFML/Graphics.hpp>

#include "GameState.h"
#include "Game.h"

class WorldMapGameState : public GameState
{
private:

	sf::View gameView;
	sf::View guiView;

public:

	virtual void draw(const float dt);
	virtual void update(const float dt);
	virtual void handleInput();

	WorldMapGameState(Game* game);
	virtual ~WorldMapGameState();
};

#endif /* GAME_STATE_EDITOR_HPP */