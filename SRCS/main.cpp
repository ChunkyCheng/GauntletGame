#include <string>
#include <sstream>
#include <iostream>
#include "raylib.h"

#include "Entity.hpp"
#include "PoincareWarpShader.hpp"

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

	{
		PoincareWarpShader	mapShader;
		

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
			DrawFPS(5, 5);
			DrawText(playerPos.str().c_str(), 5, 30, 20, RED);

			BeginShaderMode(*mapShader);
			MinkowskiCoord	relative = (dot.pos().relativeTo(player.pos()));
			mapShader.setObjInvFrame(relative.inverseRowX(), relative.inverseRowY());
			mapShader.setDiskCenter(WIN_WIDTH / 2, WIN_HEIGHT / 2);
			mapShader.setDiskRadius(MAP_RADIUS);
			mapShader.setHalfExtent(0.1);
			DrawCircle(WIN_WIDTH / 2, WIN_HEIGHT / 2, MAP_RADIUS, WHITE);
			EndShaderMode();
			EndDrawing();
		}
	}
	CloseWindow();
}
