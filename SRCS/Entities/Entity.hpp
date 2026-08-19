#pragma once

#include <memory>
#include <string>
#include "raylib.h"
#include "MinkowskiCoord.hpp"

class	Entity
{
	public:
		Entity(float x, float y, const std::string& texture);
		Entity(const Entity& other);
		Entity&	operator=(const Entity& other);
	public:
		virtual ~Entity(void) = default;

		virtual	void	updatePos(float dt);
		void			moveX(float dist);
		void			moveY(float dist);
		
		const MinkowskiCoord&	pos(void) const;
		const Texture&			texture(void) const;
		bool					hasTexture(void) const;

	private:
		MinkowskiCoord				m_pos;
		std::unique_ptr<Texture2D>	m_texturePtr;
};