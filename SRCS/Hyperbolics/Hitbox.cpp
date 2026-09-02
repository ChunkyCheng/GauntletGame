#include "Hitbox.hpp"
#include "MinkowskiCoord.hpp"

struct	HyperbolicRect
{
	Vector2	topLeft;
	Vector2	botRight;
};

Hitbox::Hitbox(float width, float height)
	: m_width(width)
	, m_height(height)
{}

Hitbox::Hitbox(const Hitbox& other) = default;

Hitbox::~Hitbox(void) {}

static HyperbolicRect	toHyperbolicRect(const Hitbox& hitbox, const MinkowskiCoord& pos)
{
	MinkowskiCoord topLeft(0, 0);
	MinkowskiCoord botRight(0, 0);

	topLeft.moveHyperbolic(hitbox.height() / 2, PI / 2);
	topLeft.moveHyperbolic(hitbox.width() / 2, PI);
	topLeft = topLeft.inverseRelativeTo(pos);
	botRight.moveHyperbolic(hitbox.height() / 2, -PI / 2);
	botRight.moveHyperbolic(hitbox.width() / 2, 0);
	botRight = botRight.inverseRelativeTo(pos);

	return {
		{topLeft.x(), topLeft.y()},
		{botRight.x(), botRight.y()}
	};
}

bool	Hitbox::collides(const MinkowskiCoord& pos, const Hitbox& other, const MinkowskiCoord& otherPos) const
{
	HyperbolicRect	rectangle1 = toHyperbolicRect(*this, pos);
	HyperbolicRect	rectangle2 = toHyperbolicRect(other, otherPos);

	if (rectangle1.topLeft.x < rectangle2.botRight.x
        && rectangle1.botRight.x > rectangle2.topLeft.x
        && rectangle1.topLeft.y > rectangle2.botRight.y
        && rectangle1.botRight.y < rectangle2.topLeft.y)
		return true;
	return false;
}

float	Hitbox::width(void) const { return m_width; }
float	Hitbox::height(void) const { return m_height; }