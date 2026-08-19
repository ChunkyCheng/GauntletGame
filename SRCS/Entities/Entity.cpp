#include "Entity.hpp"

Entity::Entity(float x, float y, const std::string& texturePath, float textureExtent, Vector2 textureOffset, float hitboxRadius)
	: m_pos(x, y)
	, m_textureExtent(textureExtent)
	, m_textureOffset(textureOffset)
	, m_hitboxRadius(hitboxRadius)
{
	if (texturePath.length() != 0)
	{
		m_texturePtr = std::make_unique<Texture>();
		*m_texturePtr = LoadTexture(texturePath.c_str());
	}
	else
		m_texturePtr = nullptr;
}

bool	Entity::collides(const Entity& other)
{
	if (m_pos.hDist(other.m_pos) < (m_hitboxRadius + other.m_hitboxRadius))
		return true;
	return false;
}

void	Entity::updatePos(float dt) { (void)dt; }
void	Entity::moveX(float dist) { m_pos.moveXHyperbolic(dist); }
void	Entity::moveY(float dist) { m_pos.moveYHyperbolic(dist); }

const MinkowskiCoord&	Entity::pos(void) const { return m_pos; }
const Texture&			Entity::texture(void) const { return *m_texturePtr; }
bool					Entity::hasTexture(void) const { return m_texturePtr ? true : false; }
float					Entity::textureExtent(void) const { return m_textureExtent; }
const Vector2&			Entity::textureOffset(void) const { return m_textureOffset; }
float					Entity::hitboxRadius(void) const { return m_hitboxRadius; }