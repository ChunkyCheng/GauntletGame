#include "Entity.hpp"

Entity::Entity(float x, float y)
	: m_pos(x, y)
{
}

void	Entity::moveX(float dist) { m_pos.moveXHyperbolic(dist); }
void	Entity::moveY(float dist) { m_pos.moveYHyperbolic(dist); }

const MinkowskiCoord&	Entity::pos(void) const { return m_pos; }