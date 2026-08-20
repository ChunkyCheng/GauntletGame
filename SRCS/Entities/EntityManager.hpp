#pragma once

#include <memory>
#include <vector>
#include <Obstacle.hpp>

class	EntityManager
{
	public:
		EntityManager(float spawnInterval, int spawnSize);
		EntityManager(const EntityManager& other);
		EntityManager&	operator=(const EntityManager& other);
		~EntityManager(void);
		
		void			reset(void);
		void			removeDespawned(void);
		void			spawn(float timeElapsed);
		virtual void	spawnRandom(void) = 0;

		const std::vector<std::unique_ptr<Obstacle>>&	entities(void) const;

	protected:
		std::vector<std::unique_ptr<Obstacle>>	m_entities;
		float									m_timeOfLastSpawn;
		float									m_spawnInterval;
		int										m_spawnSize;
};

