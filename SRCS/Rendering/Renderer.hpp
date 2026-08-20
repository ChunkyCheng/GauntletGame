#pragma once

#include <vector>
#include "raylib.h"
#include "PoincareWarpShader.hpp"
#include "Entity.hpp"

class	GameState;

class	Renderer
{
	public:
		Renderer(const GameState& gameState);
		Renderer(const Renderer& other);
		Renderer&	operator=(const Renderer& other);
		~Renderer(void);

		void	renderTextCentered(const std::string& text, int posX, int posY, int fontSize, Color color);
		void	renderEntity(Vector2 diskCenter, float diskRadius, const Entity& entity);
		void	renderEntityTextured(Vector2 diskCenter, float diskRadius, const Entity& entity);
		void	renderEntityHitbox(Vector2 diskCenter, float diskRadius, const Entity& entity);
		
		template<typename T>void	renderMap(Vector2 diskCenter, float diskRadius, const T& entities);

	protected:
	private:
		const GameState&	m_gameState;
		PoincareWarpShader	m_mapShader;
};

#include "Renderer.tpp"