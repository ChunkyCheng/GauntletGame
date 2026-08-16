#pragma once

#include "MinkowskiCoord.hpp"

class	Entity
{
	public:
		Entity(float x, float y);
		Entity(const Entity& other);
		Entity&	operator=(const Entity& other);
	public:
		virtual ~Entity(void) = default;

		void	moveX(float dist);
		void	moveY(float dist);
		
		const MinkowskiCoord&	pos(void) const;

	private:
		MinkowskiCoord	m_pos;
};

