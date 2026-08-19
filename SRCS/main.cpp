#include <string>
#include <sstream>
#include <iostream>
#include <memory>
#include <random>
#include <ctime>
#include "raylib.h"

#include "GameState.hpp"
#include "Player.hpp"
#include "ObstacleManager.hpp"
#include "Renderer.hpp"

constexpr int	WIN_WIDTH = 1280;
constexpr int	WIN_HEIGHT = 800;
constexpr int	MAP_RADIUS = WIN_HEIGHT / 2 - 10;

int	main(void)
{
	std::srand(std::time(0));
	SetTraceLogLevel(LOG_WARNING);
	InitWindow(WIN_WIDTH, WIN_HEIGHT, "hyper_long");
	SetTargetFPS(60);

	{
		GameState		gameState;
		Renderer		renderer(gameState);
		Player			player;
		ObstacleManager	obstacleManager;

		while (!WindowShouldClose())
		{
			float	dt = GetFrameTime();

			player.updatePos(dt);
			for (auto& e : obstacleManager.obstacles())
				e->updatePos(dt);
			obstacleManager.removeDespawned();
			if (IsKeyDown(KEY_S)) obstacleManager.spawnRandom();
			player.runCollisionEvents(obstacleManager.obstacles());
			BeginDrawing();
			ClearBackground(BLACK);
			
			renderer.renderMap(
				{WIN_WIDTH / 2, WIN_HEIGHT / 2},
				MAP_RADIUS,
				obstacleManager.obstacles()
			);
			renderer.renderEntity(
				{WIN_WIDTH / 2, WIN_HEIGHT / 2},
				MAP_RADIUS,
				player
			);
			DrawFPS(5, 5);

			EndDrawing();
		}
	}
	CloseWindow();
}
