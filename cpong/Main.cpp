#include "Main.h"
#include <iostream>
#include <string>
#include <tuple>

using namespace std;

void fatalError(string errorString)
{
	cout << errorString << endl;
	int a;
	cin >> a;
	SDL_Quit();
	exit(1);
}

Main::Main()
{
	_window = nullptr;
	_width = 640;
	_height = 480;
	_gamestate = GameState::PLAY;
}


Main::~Main()
{
}

void Main::run()
{
	initSystems();
	_paddle1.init(32.0f, 240.0f, 32.0f, 96.0f);
	_paddle2.init(608.0f, 240.0f, 32.0f, 96.0f);
	_ball.init(320.0f, 240.0f, 32.0f, 32.0f);
	gameLoop();
}

void Main::initSystems()
{
	SDL_Init(SDL_INIT_EVERYTHING);

	_window = SDL_CreateWindow("Pong",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED, _width, _height, SDL_WINDOW_OPENGL);
	if (_window == nullptr)
	{
		fatalError("Window could not be initialized");
	}

	SDL_GLContext glContext = SDL_GL_CreateContext(_window);
	if (glContext == nullptr)
	{
		fatalError("Context could not be initialized");
	}
	GLenum error = glewInit();
	if (error != GLEW_OK)
	{
		fatalError("GLEW could not be initialized");
	}

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0);
}

void Main::gameLoop()
{
	while (_gamestate != GameState::EXIT)
	{
		processInput();
		_ball.move();
		tuple<float, float> ballCoords = _ball.returnCoords();
		float ballAngle = _ball.returnAngle();
		tuple<float, float> p1Coords = _paddle1.returnCoords();
		tuple<float, float> p2Coords = _paddle2.returnCoords();
		if (get<1>(ballCoords) < 16.0f)
		{
			if (ballAngle == 0.25f)
			{
				_ball.bounce(4);
			}
			else
			{
				_ball.bounce(3);
			}
		}
		else if (get<1>(ballCoords) > 464.0f)
		{
			if (ballAngle == 1.25f)
			{
				_ball.bounce(2);
			}
			else
			{
				_ball.bounce(1);
			}
		}
		if (get<0>(ballCoords) < 40.0f)
		{
			if (get<0>(ballCoords) < 0.0f)
			{
				_ball.updateCoords(320.0f, 240.0f);
			}
			else if (get<1>(ballCoords) > get<1>(p1Coords) - 32.0f &&
					 get<1>(ballCoords) < get<1>(p1Coords) + 32.0f &&
					 get<0>(ballCoords) > 20.0f)
			{
				if (ballAngle == 1.25f)
				{
					_ball.bounce(4);
				}
				else
				{
					_ball.bounce(1);
				}
			}
		}
		else if (get<0>(ballCoords) > 600.0f)
		{
			if (get<0>(ballCoords) > 640.0f)
			{
				_ball.updateCoords(320.0f, 240.0f);
			}
			else if (get<1>(ballCoords) > get<1>(p2Coords) - 32.0f &&
					 get<1>(ballCoords) < get<1>(p2Coords) + 32.0f && 
					 get<0>(ballCoords) < 620.0f)
			{
				if (ballAngle == 0.25f)
				{
					_ball.bounce(2);
				}
				else
				{
					_ball.bounce(3);
				}
			}
		}
		drawGame();
	}
}

void Main::processInput()
{
	SDL_Event evnt;
	while (SDL_PollEvent(&evnt))
	{
		switch (evnt.type)
		{
		case SDL_QUIT:
			_gamestate = GameState::EXIT;
			break;
		default:
			break;
		}
	}
	void SDL_PumpEvents(void);
	if (_keystate[SDL_SCANCODE_UP])
	{
		_paddle2.moveBy(0.0f, 0.5f);
	}
	if (_keystate[SDL_SCANCODE_DOWN])
	{
		_paddle2.moveBy(0.0f, -0.5f);
	}
	if (_keystate[SDL_SCANCODE_W])
	{
		_paddle1.moveBy(0.0f, 0.5f);
	}
	if (_keystate[SDL_SCANCODE_S])
	{
		_paddle1.moveBy(0.0f, -0.5f);
	}
}

void Main::drawGame()
{
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	_paddle1.draw();
	_paddle2.draw();
	_ball.draw();
	SDL_GL_SwapWindow(_window);
}
