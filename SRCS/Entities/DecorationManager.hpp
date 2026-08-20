#pragma once

#include "EntityManager.hpp"
#include <vector>
#include <memory>

class	DecorationManager : public EntityManager
{
	public:
		DecorationManager(void);
		DecorationManager(const DecorationManager& other);
		DecorationManager&	operator=(const DecorationManager& other);
		~DecorationManager(void);
	
		void	spawnRandom(void) override;
};

