#include <string>
#include <iostream>
#include <random>
#include <ctime>
#include "raylib.h"

#include "GameState.hpp"

int	main(void)
{
	std::srand(std::time(0));
	SetTraceLogLevel(LOG_WARNING);
	InitWindow(WIN_WIDTH, WIN_HEIGHT, "Hyper Wau");
	SetTargetFPS(60);
	{
		GameState		gameState;

		while (!WindowShouldClose())
			gameState.runGameEvents();
	}
	CloseWindow();
}
