#include <string>
#include <sstream>
#include <iostream>
#include <memory>
#include "raylib.h"

#include "Player.hpp"
#include "Renderer.hpp"

constexpr int	WIN_WIDTH = 1280;
constexpr int	WIN_HEIGHT = 800;
constexpr int	MAP_RADIUS = WIN_HEIGHT / 2 - 50;

int	main(void)
{
	SetTraceLogLevel(LOG_WARNING);
	InitWindow(WIN_WIDTH, WIN_HEIGHT, "hyper_long");
	SetTargetFPS(60);

	{
		Renderer								renderer;	
		std::vector<std::unique_ptr<Entity>>	entities;

		entities.push_back(std::make_unique<Entity>(-1, 1, ""));
		entities.push_back(std::make_unique<Entity>(1, 1, ""));
		entities.push_back(std::make_unique<Player>());

		while (!WindowShouldClose())
		{
			float	dt = GetFrameTime();

			for (auto& e : entities)
				e->updatePos(dt);

			BeginDrawing();
			ClearBackground(BLACK);
			renderer.renderMap(
				{WIN_WIDTH / 2, WIN_HEIGHT / 2},
				WIN_HEIGHT / 2 - 10,
				entities
			);
			DrawFPS(5, 5);

			EndDrawing();
		}
	}
	CloseWindow();
}
