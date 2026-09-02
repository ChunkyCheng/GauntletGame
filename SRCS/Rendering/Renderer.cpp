#include "Renderer.hpp"
#include <cmath>
#include "GameState.hpp"

Renderer::Renderer(const GameState& gameState)
	: m_gameState(gameState)
{}
Renderer::~Renderer(void) {}


void	Renderer::renderTextCentered(const std::string& text, int posX, int posY, int fontSize, Color color)
{
	int	textWidth = MeasureText(text.c_str(), fontSize);

	DrawText(text.c_str(), posX - textWidth / 2, posY, fontSize, color)	;
}

void	Renderer::renderEntity(Vector2 diskCenter, float diskRadius, const Entity& entity)
{
	m_mapShader.setDiskCenter(diskCenter.x, diskCenter.y);
	m_mapShader.setDiskRadius(diskRadius);

	m_mapShader.setObjInvFrame(entity.pos().relativeRowX(), entity.pos().relativeRowY());
	renderEntityTextured(diskCenter, diskRadius, entity);
	if (m_gameState.showDebug())
		renderEntityHitbox(diskCenter, diskRadius, entity);
}

void	Renderer::renderEntityTextured(Vector2 diskCenter, float diskRadius, const Entity& entity)
{
	BeginShaderMode(*m_mapShader);
	m_mapShader.setExtent(entity.sprite().extent);
	m_mapShader.setDrawMode(PoincareWarpShader::textured);
	m_mapShader.setTextureOffset(entity.sprite().offset);

	const Texture2D*	texturePtr = m_textureManager.get(entity.sprite().texturePath);
	Rectangle	src = { 0, 0, (float)texturePtr->width, (float)texturePtr->height };
	Rectangle	dst = {
		diskCenter.x - diskRadius,
		diskCenter.y - diskRadius,
		diskCenter.x + diskRadius,
		diskCenter.y + diskRadius
	};
	DrawTexturePro(*texturePtr, src, dst, {0, 0}, 0.0, WHITE);
	EndShaderMode();
}

void	Renderer::renderEntityHitbox(Vector2 diskCenter, float diskRadius, const Entity& entity)
{
	BeginShaderMode(*m_mapShader);
	Vector2 extent = {
		std::tanh(entity.hitbox().width() / 2) * 2,
		std::tanh(entity.hitbox().height() / 2) * 2
	};
	m_mapShader.setExtent(extent);
	m_mapShader.setDrawMode(PoincareWarpShader::rectangle);
	DrawCircle(diskCenter.x, diskCenter.y, diskRadius, entity.hitboxColor());
	EndShaderMode();
}