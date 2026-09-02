#include "Entity.hpp"

Entity::Entity(float x, float y, const std::string& texturePath, Sprite sprite, float hitboxRadius)
	: m_pos(x, y)
	, m_sprite(sprite)
	, m_hitboxRadius(hitboxRadius)
	, m_hitboxColor(RED)
{
	if (texturePath.length() != 0)
	{
		m_texturePtr = std::make_unique<Texture>();
		*m_texturePtr = LoadTexture(texturePath.c_str());
	}
	else
		m_texturePtr = nullptr;
}

bool	Entity::collides(const Entity& other) const
{
	if (m_pos.hDist(other.m_pos) < (m_hitboxRadius + other.m_hitboxRadius))
		return true;
	return false;
}

void	Entity::collisionEvent(const Entity& other)
{
	(void)other;
}


void	Entity::updatePos(float dt) { (void)dt; }
void	Entity::moveX(float dist) { m_pos.moveXHyperbolic(dist); }
void	Entity::moveY(float dist) { m_pos.moveYHyperbolic(dist); }
void	Entity::move(float dist, float degrees) { m_pos.moveHyperbolic(dist, degrees * DEG2RAD); }

const MinkowskiCoord&	Entity::pos(void) const { return m_pos; }
const Texture&			Entity::texture(void) const { return *m_texturePtr; }
bool					Entity::hasTexture(void) const { return m_texturePtr ? true : false; }
const Sprite&			Entity::sprite(void) const { return m_sprite; }
float					Entity::hitboxRadius(void) const { return m_hitboxRadius; }
const Color&			Entity::hitboxColor(void) const { return m_hitboxColor; }

void					Entity::setHitboxColor(const Color& color) { m_hitboxColor = color; }