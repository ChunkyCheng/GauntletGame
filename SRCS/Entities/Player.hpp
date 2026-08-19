#pragma once

#include "Entity.hpp"

constexpr float	PLAYER_MOVE_DIST = 2;

class	Player : public Entity
{
	public:
		Player(void);
		Player(const Player& other);
		Player&	operator=(const Player& other);
		~Player(void);

		bool	isAlive(void) const;

		void	updatePos(float dt);
		void	collisionEvent(const Entity& other);
	
	private:
		bool	m_isAlive = true;
};

