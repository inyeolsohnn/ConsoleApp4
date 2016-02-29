#ifndef GAME_H
#define GAME_H
#include<stack>
#include<SFML/Graphics.hpp>
#include "TextureManager.h"
#include "Tile.h"
#include "Actor.h"
class GameState;

	class Game
{
private:
	void loadTextures();
	void loadTiles();
public:
	
	Tile tile;
	
	std::map<std::string, Tile> tileAtlas;
	std::map<std::string, Active*> activeAtlas;
	std::stack<GameState*> states;
	sf::RenderWindow window;
	TextureManager texmgr;
	void pushState(GameState* state);
	void popState();
	void changeState(GameState* state);
	GameState* peekState();
	sf::Sprite background;
	sf::Texture tex;
	Game();
	~Game();
};
#endif

