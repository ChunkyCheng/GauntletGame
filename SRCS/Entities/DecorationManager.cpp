#include "DecorationManager.hpp"
#include <random>
#include "PoincareCoord.hpp"

DecorationManager::DecorationManager(void)
	: EntityManager(1, 1)
{}

DecorationManager::~DecorationManager(void) {}

void	DecorationManager::spawnRandom(void)
{
	float	angle = (std::rand() % 8) * 45 + 10;
	float	x = -std::sin((180 - angle) * DEG2RAD) * 0.99;
	float	y = std::cos((180 - angle) * DEG2RAD) * 0.99;

	MinkowskiCoord	pos = PoincareCoord(x, y).toMinkowski();
	angle += 2 / (std::rand() % 10 + 1) - 1;
	float	speed = (std::rand() % 5) / 4 * 0.2 + 0.3;
	float	size = (std::rand() % 10) / 9 * 0.2 + 0.1;
	m_entities.push_back(std::make_unique<Obstacle>(pos.x(), pos.y(), "textures/cloud-transparent.png", speed, angle, size));
}