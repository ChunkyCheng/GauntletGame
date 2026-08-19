#include "Renderer.hpp"
Renderer::Renderer(void) {}
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
		m_mapShader.setHalfExtent(0.15);
		if (e->hasTexture())
		{
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
			m_mapShader.setDrawMode(PoincareWarpShader::circle);
			DrawCircle(diskCenter.x, diskCenter.y, diskRadius, WHITE);
		}
		EndShaderMode();
	}
}