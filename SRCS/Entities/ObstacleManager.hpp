#pragma once

#include "EntityManager.hpp"
#include <memory>
#include <vector>
#include <Obstacle.hpp>

class	ObstacleManager : public EntityManager
{
	public:
		ObstacleManager(void);
		ObstacleManager(const ObstacleManager& other);
		ObstacleManager&	operator=(const ObstacleManager& other);
		~ObstacleManager(void);

		void	spawnRandom(void) override;


};

