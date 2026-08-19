#include "Renderer.hpp"
#include <cmath>
#include "GameState.hpp"

Renderer::Renderer(const GameState& gameState)
	: m_gameState(gameState)
{}
Renderer::~Renderer(void) {}

void	Renderer::renderMap(Vector2 diskCenter, float diskRadius, const std::vector<std::unique_ptr<Entity>>& entities)
{
	DrawCircle(diskCenter.x, diskCenter.y, diskRadius, WHITE);
	
	m_mapShader.setDiskCenter(diskCenter.x, diskCenter.y);
	m_mapShader.setDiskRadius(diskRadius);

	for (const auto& e : entities)
	{
		BeginShaderMode(*m_mapShader);
		m_mapShader.setObjInvFrame(e->pos().inverseRowX(), e->pos().inverseRowY());
		if (e->hasTexture())
		{
			m_mapShader.setHalfExtent(e->textureExtent() / 2);
			m_mapShader.setDrawMode(PoincareWarpShader::textured);
			Rectangle	src = { 0, 0, (float)e->texture().width, (float)e->texture().height };
			Rectangle	dst = {
				diskCenter.x - diskRadius,
				diskCenter.y - diskRadius,
				diskCenter.x + diskRadius,
				diskCenter.y + diskRadius
			};
			DrawTexturePro(e->texture(), src, dst, {0, 0}, 0.0, WHITE);
		}
		else
		{
			m_mapShader.setHalfExtent(std::tanh(e->hitboxRadius() / 2.0));
			m_mapShader.setDrawMode(PoincareWarpShader::circle);
			DrawCircle(diskCenter.x, diskCenter.y, diskRadius, WHITE);
		}
		EndShaderMode();
		if (e->hasTexture() && m_gameState.showDebug())
		{
			BeginShaderMode(*m_mapShader);
			m_mapShader.setHalfExtent(std::tanh(e->hitboxRadius() / 2.0));
			m_mapShader.setDrawMode(PoincareWarpShader::circle);
			DrawCircle(diskCenter.x, diskCenter.y, diskRadius, WHITE);
			EndShaderMode();
		}
	}
}