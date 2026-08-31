#include "Player.hpp"
#include "raylib.h"
#include <cmath>
#include "PoincareCoord.hpp"

Player::Player(void)
	: Entity(0, 0, "textures/wau.png", 0.5, {0, 0.04}, 0.2)
	, m_isAlive(true)
{
}

Player::~Player(void)
{
}

void	Player::reset(void)
{
	m_isAlive = true;
	m_xHeading = 0;
	m_yHeading = 0;
	m_pos = MinkowskiCoord(0, 0);
}

void	Player::updatePos(float dt)
{
	float	dist = PLAYER_MOVE_DIST * dt;

	if (IsKeyDown(KEY_UP))		m_pos.moveHyperbolic(dist, m_yHeading);
	if (IsKeyDown(KEY_DOWN))	m_pos.moveHyperbolic(-dist, m_yHeading);
	if (IsKeyDown(KEY_LEFT))	m_pos.moveHyperbolic(-dist, m_xHeading);
	if (IsKeyDown(KEY_RIGHT))	m_pos.moveHyperbolic(dist, m_xHeading);
	if (IsKeyDown(KEY_R)) m_isAlive = false;

	updateXHeading();
	updateYHeading();

	// Vector2	move = {0, 0};

	// if (IsKeyDown(KEY_UP))		move.y += PLAYER_MOVE_DIST;
	// if (IsKeyDown(KEY_DOWN))	move.y -= PLAYER_MOVE_DIST;
	// if (IsKeyDown(KEY_LEFT))	move.x -= PLAYER_MOVE_DIST;
	// if (IsKeyDown(KEY_RIGHT))	move.x += PLAYER_MOVE_DIST;

	// if (move.x != 0 && move.y != 0)
	// {
	// 	float root2 = std::sqrt(2);
	// 	move.x /= root2;
	// 	move.y /= root2;
	// }

	// m_pos.moveXHyperbolic(move.x * dt);
	// m_pos.moveYHyperbolic(move.y * dt);
	// if (m_pos.hDist(MinkowskiCoord(0, 0)) > 4)
	// 	m_isAlive = false;
}

void	Player::updateXHeading(void)
{

	if (std::fabs(m_pos.x() * m_pos.y()) <= 1e-4f)
		m_xHeading = 0;
	else
	{
		float	gradient = m_pos.x() * m_pos.y() / (m_pos.z() - m_pos.x() - 1);
		m_xHeading = std::atan(gradient);
	}
}

void	Player::updateYHeading(void)
{
	if (std::fabs(m_pos.x() * m_pos.y()) <= 1e-4f)
		m_yHeading = PI / 2;
	else
	{
		float	gradient = m_pos.x() * m_pos.y() / (m_pos.z() - m_pos.y() - 1);
		m_yHeading = PI / 2 - std::atan(gradient);
	}
}

void	Player::collisionEvent(const Entity& other)
{
	(void)other;
	m_isAlive = false;
	setHitboxColor(GREEN);
}

bool	Player::isAlive(void) const { return m_isAlive; }