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
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> dis(-0.8f, 0.8f);

	float	x = dis(gen);
	float	y = std::sqrt(0.8 - (x * x));
	if (std::rand() % 2)
		y *= -1;
	
	MinkowskiCoord	pos = PoincareCoord(x, y).toMinkowski();
	m_obstacles.push_back(std::make_unique<Obstacle>(pos.x(), pos.y(), 1, 0));
}


const std::vector<std::unique_ptr<Obstacle>>&	ObstacleManager::obstacles(void) const { return m_obstacles; }