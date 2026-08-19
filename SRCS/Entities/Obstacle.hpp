#pragma once

#include "Entity.hpp"

class	Obstacle : public Entity
{
	public:
		Obstacle(float x, float y, float moveSpeed, float moveAngle);
		Obstacle(const Obstacle& other);
		Obstacle&	operator=(const Obstacle& other);
		~Obstacle(void);

		void	updatePos(float dt);

		bool	shouldDespawn(void) const;

	protected:
	private:
		Vector2	m_moveVector;
		bool	m_shouldDespawn;
};