#include "ObstacleManager.hpp"
#include <random>
#include "PoincareCoord.hpp"

ObstacleManager::ObstacleManager(void)
	: EntityManager(2.5, 4)
{}

ObstacleManager::~ObstacleManager(void) {}

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
	
	float	speed = 1.5;
	float	size = 0.5;
	if ((std::rand() % 20) == 0)
	{	
		speed = 0.8;
		size = 1;
	}
	m_entities.push_back(std::make_unique<Obstacle>(pos.x(), pos.y(), texturePath, speed, angle, size));
}

