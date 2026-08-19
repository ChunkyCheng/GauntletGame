#include "Renderer.hpp"
#include <cmath>
#include "GameState.hpp"

Renderer::Renderer(const GameState& gameState)
	: m_gameState(gameState)
{}
Renderer::~Renderer(void) {}
void	Renderer::renderEntity(Vector2 diskCenter, float diskRadius, const Entity& entity)
{
	m_mapShader.setDiskCenter(diskCenter.x, diskCenter.y);
	m_mapShader.setDiskRadius(diskRadius);

	m_mapShader.setObjInvFrame(entity.pos().inverseRowX(), entity.pos().inverseRowY());
	if (entity.hasTexture())
		renderEntityTextured(diskCenter, diskRadius, entity);
	if (m_gameState.showDebug())
		renderEntityHitbox(diskCenter, diskRadius, entity);
}

void	Renderer::renderEntityTextured(Vector2 diskCenter, float diskRadius, const Entity& entity)
{
	BeginShaderMode(*m_mapShader);
	m_mapShader.setHalfExtent(entity.textureExtent() / 2);
	m_mapShader.setDrawMode(PoincareWarpShader::textured);
	m_mapShader.setTextureOffset(entity.textureOffset());
	Rectangle	src = { 0, 0, (float)entity.texture().width, (float)entity.texture().height };
	Rectangle	dst = {
		diskCenter.x - diskRadius,
		diskCenter.y - diskRadius,
		diskCenter.x + diskRadius,
		diskCenter.y + diskRadius
	};
	DrawTexturePro(entity.texture(), src, dst, {0, 0}, 0.0, WHITE);
	EndShaderMode();
}

void	Renderer::renderEntityHitbox(Vector2 diskCenter, float diskRadius, const Entity& entity)
{
	BeginShaderMode(*m_mapShader);
	m_mapShader.setHalfExtent(std::tanh(entity.hitboxRadius() / 2.0));
	m_mapShader.setDrawMode(PoincareWarpShader::circle);
	DrawCircle(diskCenter.x, diskCenter.y, diskRadius, entity.hitboxColor());
	EndShaderMode();
}