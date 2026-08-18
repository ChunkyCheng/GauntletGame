#include "Player.hpp"
#include "raylib.h"

Player::Player(void)
	: Entity(0, 0, LoadTexture("textures/wau.png"))
{
}

Player::~Player(void)
{
}

void	Player::updatePos(float dt)
{
	if (IsKeyDown(KEY_UP)) moveY(PLAYER_MOVE_DIST * dt);
	if (IsKeyDown(KEY_DOWN)) moveY(-PLAYER_MOVE_DIST * dt);
	if (IsKeyDown(KEY_LEFT)) moveX(-PLAYER_MOVE_DIST * dt);
	if (IsKeyDown(KEY_RIGHT)) moveX(PLAYER_MOVE_DIST * dt);
}