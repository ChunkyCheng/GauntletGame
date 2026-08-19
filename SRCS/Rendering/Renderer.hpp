#pragma once

#include <vector>
#include "raylib.h"
#include "PoincareWarpShader.hpp"
#include "Entity.hpp"

class	Renderer
{
	public:
		Renderer(void);
		Renderer(const Renderer& other);
		Renderer&	operator=(const Renderer& other);
		~Renderer(void);

		void	renderMap(Vector2 diskCenter, float diskRadius, const std::vector<std::unique_ptr<Entity>>& entities);

	protected:
	private:
		PoincareWarpShader	m_mapShader;
};

