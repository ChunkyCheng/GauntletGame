#include "Entity.hpp"

Entity::Entity(float x, float y, Texture texture)
	: m_pos(x, y)
	, m_texture(texture)
{
}

void	Entity::moveX(float dist) { m_pos.moveXHyperbolic(dist); }
void	Entity::moveY(float dist) { m_pos.moveYHyperbolic(dist); }

const MinkowskiCoord&	Entity::pos(void) const { return m_pos; }
const Texture&			Entity::texture(void) const { return m_texture; }