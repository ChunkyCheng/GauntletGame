#include "Entity.hpp"

Entity::Entity(float x, float y, const std::string& texturePath)
	: m_pos(x, y)
{
	if (texturePath.length() != 0)
	{
		m_texturePtr = std::make_unique<Texture>();
		*m_texturePtr = LoadTexture(texturePath.c_str());
	}
	else
		m_texturePtr = nullptr;
}

void	Entity::updatePos(float dt) { (void)dt; }
void	Entity::moveX(float dist) { m_pos.moveXHyperbolic(dist); }
void	Entity::moveY(float dist) { m_pos.moveYHyperbolic(dist); }

const MinkowskiCoord&	Entity::pos(void) const { return m_pos; }
const Texture&			Entity::texture(void) const { return *m_texturePtr; }

bool					Entity::hasTexture(void) const
{
	if (m_texturePtr)
		return true;
	return false;
}