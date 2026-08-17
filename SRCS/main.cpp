#include <string>
#include <sstream>
#include <iostream>
#include "raylib.h"

#include "Entity.hpp"

constexpr int	WIN_WIDTH = 1280;
constexpr int	WIN_HEIGHT = 720;
constexpr int	MAP_RADIUS = WIN_HEIGHT / 2 - 50;
constexpr float	PLAYER_MOVE_DIST = 2;

int	main(void)
{
	Entity	player(0, 0);
	Entity	dot(0, 0);
	float	dt = GetFrameTime();

	SetTraceLogLevel(LOG_WARNING);
	InitWindow(WIN_WIDTH, WIN_HEIGHT, "hyper_long");
	SetTargetFPS(60);
	while (!WindowShouldClose())
	{
		dt = GetFrameTime() - dt;
		if (IsKeyDown(KEY_UP)) player.moveY(PLAYER_MOVE_DIST * dt);
		if (IsKeyDown(KEY_DOWN)) player.moveY(-PLAYER_MOVE_DIST * dt);
		if (IsKeyDown(KEY_LEFT)) player.moveX(-PLAYER_MOVE_DIST * dt);
		if (IsKeyDown(KEY_RIGHT)) player.moveX(PLAYER_MOVE_DIST * dt);

		std::stringstream	playerPos;

		playerPos << player.pos();

		BeginDrawing();
		ClearBackground(BLACK);
		DrawCircle(WIN_WIDTH / 2, WIN_HEIGHT / 2, MAP_RADIUS, WHITE);
		PoincareCoord	p = (dot.pos().relativeTo(player.pos())).toPoincare();

		DrawCircle(
			WIN_WIDTH / 2 + p.x() * MAP_RADIUS,
			WIN_HEIGHT / 2 - p.y() * MAP_RADIUS,
			5,
			RED
		);
		DrawText(playerPos.str().c_str(), 5, 5, 20, RED);
		EndDrawing();
	}
	CloseWindow();
}
