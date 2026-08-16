#include <string>
#include <iostream>
#include "raylib.h"
#include "MinkowskiCoord.hpp"

constexpr int WIN_WIDTH = 1280;
constexpr int WIN_HEIGHT = 920;

int	main(void)
{
	MinkowskiCoord	c(1230, -4800);

	std::cout << "minkowski: " << c << "\n";
	std::cout << "poincare:  " << c.toPoincare() << "\n";

	InitWindow(WIN_WIDTH, WIN_HEIGHT, "hyper_long");
	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(RAYWHITE);
		DrawText("Hello there!", 400, 225, 20, LIGHTGRAY);
		EndDrawing();
	}
	CloseWindow();
}
