#include "ObstacleManager.hpp"
#include <random>
#include "PoincareCoord.hpp"

ObstacleManager::ObstacleManager(void) {}
ObstacleManager::~ObstacleManager(void) {}

void	ObstacleManager::removeDespawned(void)
{
	for (auto it = m_obstacles.begin(); it != m_obstacles.end();)
	{
		if (it->get()->shouldDespawn())
			it = m_obstacles.erase(it);
		else
			++it;
	}
}

void	ObstacleManager::spawnRandom(void)
{

	float	angle = (std::rand() % 8) * 45;
	float	x = -std::sin((180 - angle) * DEG2RAD) * 0.99;
	float	y = std::cos((180 - angle) * DEG2RAD) * 0.99;

	MinkowskiCoord	pos = PoincareCoord(x, y).toMinkowski();
	angle += 2 / (std::rand() % 10 + 1) - 1;
	std::string	texturePath;
	if (angle < 180)
		texturePath = "textures/helicopter-right.png";
	else
		texturePath = "textures/helicopter-left.png";
	m_obstacles.push_back(std::make_unique<Obstacle>(pos.x(), pos.y(), texturePath, 1.5, angle, 0.3));

}


const std::vector<std::unique_ptr<Obstacle>>&	ObstacleManager::obstacles(void) const { return m_obstacles; }