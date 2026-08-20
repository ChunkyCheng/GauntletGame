#include <cmath>
#include <GameState.hpp>

template <typename T>
void	Renderer::renderMap(Vector2 diskCenter, float diskRadius, const T& entities)
{
	
	for (const auto& e : entities)
		renderEntity(diskCenter, diskRadius, *e);
}	
