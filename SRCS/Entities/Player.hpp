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

		void	reset(void);
		void	updatePos(float dt);
		void	updateXHeading(void);
		void	updateYHeading(void);
		void	collisionEvent(const Entity& other);
	
		bool	isAlive(void) const;

	private:
		bool	m_isAlive;
		float	m_xHeading;
		float	m_yHeading;
};

