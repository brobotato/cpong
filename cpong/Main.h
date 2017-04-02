#pragma once
#include "Sprite.h"
#include <SDL/SDL.h>
#include <GL/glew.h>

enum class GameState {PLAY,EXIT};

class Main
{
public:
	Main();
	~Main();

	void run();

private:
	void initSystems();
	void processInput();
	void gameLoop();
	void drawGame();

	SDL_Window* _window;
	const Uint8 *_keystate = SDL_GetKeyboardState(NULL);
	int _width;
	int _height;
	GameState _gamestate;
	Sprite _paddle1;
	Sprite _paddle2;
	Ball _ball;
};
