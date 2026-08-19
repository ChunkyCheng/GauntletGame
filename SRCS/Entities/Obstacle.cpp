#include "Obstacle.hpp"
#include <cmath>

Obstacle::Obstacle(float x, float y, float moveSpeed, float moveAngle, float hitboxRadius)
	: Entity(x, y, "textures/helicopter.png", hitboxRadius * 1.2, {0, 0}, hitboxRadius)
	, m_shouldDespawn(false)
{
	float angleRad = moveAngle * DEG2RAD;
	m_moveVector = {
		std::sin(angleRad) * moveSpeed,
		std::cos(angleRad) * moveSpeed
	};
}

Obstacle::~Obstacle(void) {}

void	Obstacle::updatePos(float dt)
{
	if (m_shouldDespawn)
		return ;
	if (pos().z() > 100)
		m_shouldDespawn = true;

	moveX(m_moveVector.x * dt);
	moveY(m_moveVector.y * dt);
}

bool	Obstacle::shouldDespawn(void) const { return m_shouldDespawn; }