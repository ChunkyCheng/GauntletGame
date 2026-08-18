#pragma once

#include "raylib.h"
#include "MinkowskiCoord.hpp"

class	Entity
{
	public:
		Entity(float x, float y, Texture texture);
		Entity(const Entity& other);
		Entity&	operator=(const Entity& other);
	public:
		virtual ~Entity(void) = default;

		void	moveX(float dist);
		void	moveY(float dist);
		
		const MinkowskiCoord&	pos(void) const;
		const Texture&			texture(void) const;

	private:
		MinkowskiCoord	m_pos;
		Texture2D		m_texture;
};