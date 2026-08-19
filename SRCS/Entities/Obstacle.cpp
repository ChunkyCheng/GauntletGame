#include "Obstacle.hpp"
#include <cmath>

Obstacle::Obstacle(float x, float y, float moveSpeed, float moveAngle)
	: Entity(x, y, "", 0, {0, 0}, 1)
{
	float angleRad = moveAngle * DEG2RAD;
	m_moveVector = {
		std::sin(angleRad) / moveSpeed,
		std::cos(angleRad) / moveSpeed
	};
}

Obstacle::~Obstacle(void) {}

void	Obstacle::updatePos(float dt)
{
	moveX(m_moveVector.x * dt);
	moveY(m_moveVector.y * dt);
}