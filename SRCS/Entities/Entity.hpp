#pragma once

#include <memory>
#include <string>
#include <vector>
#include "raylib.h"
#include "MinkowskiCoord.hpp"
#include "Sprite.hpp"

class	Entity
{
	public:
		Entity(float x, float y, Sprite sprite, float hitboxRadius);
		Entity(const Entity& other);
		Entity&	operator=(const Entity& other);
	public:
		virtual ~Entity(void) = default;

		virtual	void	updatePos(float dt);
		void			moveX(float dist);
		void			moveY(float dist);
		void			move(float dist, float degrees);
	
		bool						collides(const Entity& other) const;
		template<typename T>void	runCollisionEvents(const T& others);
		virtual	void				collisionEvent(const Entity& other);

		const MinkowskiCoord&	pos(void) const;
		bool					hasTexture(void) const;
		const Sprite&			sprite(void) const;
		float					hitboxRadius(void) const;
		const Color&			hitboxColor(void) const;

		void					setHitboxColor(const Color& color);

	protected:
		MinkowskiCoord				m_pos;
		Sprite						m_sprite;
		float						m_hitboxRadius;
		Color						m_hitboxColor;
};

#include "Entity.tpp"