#include "EntityManager.hpp"

EntityManager::EntityManager(float spawnInterval, int spawnSize)
	: m_timeOfLastSpawn(0)
	, m_spawnInterval(spawnInterval)
	, m_spawnSize(spawnSize)
{}

EntityManager::~EntityManager(void) {}

void	EntityManager::reset(void)
{
	m_entities.clear();
	m_timeOfLastSpawn = 0;
}

void	EntityManager::removeDespawned(void)
{
	for (auto it = m_entities.begin(); it != m_entities.end();)
	{
		if (it->get()->shouldDespawn())
			it = m_entities.erase(it);
		else
			++it;
	}
}

void	EntityManager::spawn(float timeElapsed)
{
	if (timeElapsed - m_timeOfLastSpawn > m_spawnInterval)
	{
		for (int i = 0; i < m_spawnSize; ++i)
			spawnRandom();
		m_timeOfLastSpawn = timeElapsed;
	}
}

const std::vector<std::unique_ptr<Obstacle>>&	EntityManager::entities(void) const { return m_entities; }