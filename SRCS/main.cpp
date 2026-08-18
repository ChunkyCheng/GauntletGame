#include <string>
#include <sstream>
#include <iostream>
#include "raylib.h"

#include "Player.hpp"
#include "PoincareWarpShader.hpp"

constexpr int	WIN_WIDTH = 1280;
constexpr int	WIN_HEIGHT = 800;
constexpr int	MAP_RADIUS = WIN_HEIGHT / 2 - 50;

int	main(void)
{
	SetTraceLogLevel(LOG_WARNING);
	InitWindow(WIN_WIDTH, WIN_HEIGHT, "hyper_long");
	SetTargetFPS(60);

	{
		PoincareWarpShader	mapShader;
		Player				player;		

		while (!WindowShouldClose())
		{
			float	dt = GetFrameTime();

			std::stringstream	playerPos;
			playerPos << player.pos();

			player.updatePos(dt);

			BeginDrawing();
			ClearBackground(BLACK);
			DrawCircle(WIN_WIDTH / 2, WIN_HEIGHT / 2, MAP_RADIUS, WHITE);
			DrawFPS(5, 5);
			DrawText(playerPos.str().c_str(), 5, 30, 20, RED);

			BeginShaderMode(*mapShader);
			mapShader.setObjInvFrame(player.pos().inverseRowX(), player.pos().inverseRowY());
			mapShader.setDiskCenter(WIN_WIDTH / 2, WIN_HEIGHT / 2);
			mapShader.setDiskRadius(MAP_RADIUS);
			mapShader.setHalfExtent(0.15);
			Rectangle	src = { 0, 0, (float)player.texture().width, (float)player.texture().height };
			Rectangle	dst = { 0, 0, WIN_WIDTH, WIN_HEIGHT };
			DrawTexturePro(player.texture(), src, dst, {0, 0}, 0.0, WHITE);
			EndShaderMode();
			EndDrawing();
		}
	}
	CloseWindow();
}
