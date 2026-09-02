#include "ObstacleManager.hpp"
#include <random>
#include "PoincareCoord.hpp"
#include "TextureManager.hpp"

ObstacleManager::ObstacleManager(void)
	: EntityManager(0.1, 1)
{
}

ObstacleManager::~ObstacleManager(void) {}

void	ObstacleManager::spawnRandom(void)
{
	static int test;
	if (test)
		return ;

	m_entities.push_back(std::make_unique<Obstacle>(0, 0, "", 0, 0, 0));
	m_entities.push_back(std::make_unique<Obstacle>(1.17520119, 0, "", 0, 0, 0));
	m_entities.push_back(std::make_unique<Obstacle>(-1.17520119, 0, "", 0, 0, 0));
	m_entities.push_back(std::make_unique<Obstacle>(0, 1.17520119, "", 0, 0, 0));
	m_entities.push_back(std::make_unique<Obstacle>(0, -1.17520119, "", 0, 0, 0));
	
	test = 1;
	return ;

	float	angle = (std::rand() % 8) * 45;
	float	x = -std::sin((180 - angle) * DEG2RAD) * 0.99;
	float	y = std::cos((180 - angle) * DEG2RAD) * 0.99;

	MinkowskiCoord	pos = PoincareCoord(x, y).toMinkowski();
	angle += 2 / (std::rand() % 10 + 1) - 1;
	std::string	texturePath;
	if (angle < 180)
		texturePath = HELICOPTER_RIGHT_TEXTURE;
	else
		texturePath = HELICOPTER_LEFT_TEXTURE;
	
	float	speed = 1.7;
	float	size = 0.7;
	if ((std::rand() % 20) == 0)
	{	
		speed = 0.7;
		size = 0.9;
	}
	m_entities.push_back(std::make_unique<Obstacle>(pos.x(), pos.y(), texturePath, speed, angle, size));
}

