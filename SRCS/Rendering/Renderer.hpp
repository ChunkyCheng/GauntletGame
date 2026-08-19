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

		void	renderMap(Vector2 diskCenter, float diskRadius, const std::vector<std::unique_ptr<Entity>>& entities);

	protected:
	private:
		const GameState&	m_gameState;
		PoincareWarpShader	m_mapShader;
};

