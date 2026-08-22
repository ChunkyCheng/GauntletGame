#pragma once

#include <memory>
#include <string>
#include <vector>
#include "raylib.h"
#include "MinkowskiCoord.hpp"

class	Entity
{
	public:
		Entity(float x, float y, const std::string& texture, float textureExtent, Vector2 textureOffset, float hitboxRadius);
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
		const Texture&			texture(void) const;
		bool					hasTexture(void) const;
		float					textureExtent(void) const;
		const Vector2&			textureOffset(void) const;
		float					hitboxRadius(void) const;
		const Color&			hitboxColor(void) const;

		void					setHitboxColor(const Color& color);

	protected:
		MinkowskiCoord				m_pos;
		std::unique_ptr<Texture2D>	m_texturePtr;
		float						m_textureExtent;
		Vector2						m_textureOffset;
		float						m_hitboxRadius;
		Color						m_hitboxColor;
};

#include "Entity.tpp"