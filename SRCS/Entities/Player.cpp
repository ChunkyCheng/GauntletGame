#include "Player.hpp"
#include "raylib.h"
#include <cmath>

Player::Player(void)
	: Entity(0, 0, "textures/wau.png", 0.3, 0.2)
{
}

Player::~Player(void)
{
}

void	Player::updatePos(float dt)
{
	Vector2	move = {0, 0};

	if (IsKeyDown(KEY_UP))		move.y += PLAYER_MOVE_DIST;
	if (IsKeyDown(KEY_DOWN))	move.y -= PLAYER_MOVE_DIST;
	if (IsKeyDown(KEY_LEFT))	move.x -= PLAYER_MOVE_DIST;
	if (IsKeyDown(KEY_RIGHT))	move.x += PLAYER_MOVE_DIST;

	if (move.x != 0 && move.y != 0)
	{
		float root2 = std::sqrt(2);
		move.x /= root2;
		move.y /= root2;
	}

	moveX(move.x * dt);
	moveY(move.y * dt);
}