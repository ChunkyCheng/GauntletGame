#include "Player.hpp"
#include "raylib.h"
#include <cmath>
#include "PoincareCoord.hpp"
#include "TextureManager.hpp"

Player::Player(void)
	: Entity(0, 0, {static_cast<std::string>(PLAYER_TEXTURE), {0.5, 0.5}, {0, 0.04}}, 0.2)
	, m_isAlive(true)
{
}

Player::~Player(void)
{
}

void	Player::reset(void)
{
	m_isAlive = true;
	m_pos = MinkowskiCoord(0, 0);
}

void	Player::updatePos(float dt)
{
	Vector2	inputVector = {0, 0};

	if (IsKeyDown(KEY_UP))		inputVector.y += 1;
	if (IsKeyDown(KEY_DOWN))	inputVector.y -= 1;
	if (IsKeyDown(KEY_LEFT))	inputVector.x -= 1;
	if (IsKeyDown(KEY_RIGHT))	inputVector.x += 1;
	if (!inputVector.x && !inputVector.y)
		return ;

	float	inputAngle = std::atan2(inputVector.y, inputVector.x);
	float	sin = std::sin(inputAngle);
	float	cos = std::cos(inputAngle);
	Vector2	normal = {
		-(m_pos.y() * m_pos.y() + m_pos.z() + 1) * sin - m_pos.x() * m_pos.y() * cos,
		(m_pos.x() * m_pos.x() + m_pos.z() + 1) * cos + m_pos.x() * m_pos.y() * sin
	};
	float	heading = std::atan2(-normal.x, normal.y);
	
	float	dist = PLAYER_MOVE_DIST * dt;
	m_pos.moveHyperbolic(dist, heading);
}

void	Player::collisionEvent(const Entity& other)
{
	(void)other;
	m_isAlive = false;
	setHitboxColor(GREEN);
}
bool	Player::isAlive(void) const { return m_isAlive; }