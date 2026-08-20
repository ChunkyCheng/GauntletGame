#pragma once

#include <memory>
#include <vector>
#include <Obstacle.hpp>

class	ObstacleManager
{
	public:
		ObstacleManager(void);
		ObstacleManager(const ObstacleManager& other);
		ObstacleManager&	operator=(const ObstacleManager& other);
		~ObstacleManager(void);

		void	reset(void);
		void	removeDespawned(void);
		void	spawn(float timeElapsed);
		void	spawnRandom(void);

		const std::vector<std::unique_ptr<Obstacle>>&	obstacles(void) const;

	protected:
	private:
		std::vector<std::unique_ptr<Obstacle>>	m_obstacles;
		float									m_timeOfLastSpawn;
};

