#include "Obstacle.hpp"
#include <cmath>
#include "KleinCoord.hpp"

Obstacle::Obstacle(float x, float y, const std::string& texturePath, float moveSpeed, float moveAngle, float hitboxRadius)
	: Entity(x, y, {texturePath, {1.0f, 1.5f}, {0, -0.15}}, Hitbox(1, 0.8, KleinCoord(0, 0)))
	, m_moveSpeed(moveSpeed)
	, m_moveAngle(moveAngle)
	, m_shouldDespawn(false)
	, m_sfx(LoadMusicStream("sfx/helicopter.mp3"))
{
	(void)hitboxRadius;
	float angleRad = moveAngle * DEG2RAD;
	m_moveVector = {
		std::sin(angleRad) * moveSpeed,
		std::cos(angleRad) * moveSpeed
	};
	m_sfx.looping = true;
	PlayMusicStream(m_sfx);
	SeekMusicStream(m_sfx, std::rand() % 9);
	SetMusicPitch(m_sfx, 1.0 + (std::rand() % 100) / 99 * 0.4);
	m_sfxVolumeEx = 0.2;
}

Obstacle::~Obstacle(void)
{
	UnloadMusicStream(m_sfx);
}

void	Obstacle::updatePos(float dt)
{
	if (m_shouldDespawn)
		return ;
	if (m_pos.z() > 100)
		m_shouldDespawn = true;

	moveX(m_moveVector.x * dt);
	moveY(m_moveVector.y * dt);

	float	toCenter = m_pos.hDist(MinkowskiCoord(0, 0));
	SetMusicVolume(m_sfx, std::min((1 + m_sfxVolumeEx) / (toCenter * 3) + m_sfxVolumeEx, 5.0f));
	UpdateMusicStream(m_sfx);
}

bool	Obstacle::shouldDespawn(void) const { return m_shouldDespawn; }