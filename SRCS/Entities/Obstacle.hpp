#pragma once

#include "Entity.hpp"

class	Obstacle : public Entity
{
	public:
		Obstacle(float x, float y, const std::string& texturePath, float moveSpeed, float moveAngle, float hitboxRadius);
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