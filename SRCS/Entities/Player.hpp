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

		void	updatePos(float dt);
};

