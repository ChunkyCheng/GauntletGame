#include "Hitbox.hpp"
#include <iostream>
#include <cmath>
#include "MinkowskiCoord.hpp"
#include "KleinCoord.hpp"

struct	HyperbolicRect
{
	Vector2	topLeft;
	Vector2	botRight;
};

Hitbox::Hitbox(float width, float height)
	: m_width(width)
	, m_height(height)
{}

bool	isPointInRect(const KleinCoord& topLeft, const KleinCoord& botRight, const KleinCoord& point)
{
	if (point.x() > topLeft.x() && point.x() < botRight.x() && point.y() < topLeft.y() && point.y() > botRight.y())
		return true;
	return false;
}

bool	cornerCollides(const Hitbox& hitbox, const MinkowskiCoord& pos, const Hitbox& other, const MinkowskiCoord& otherPos)
{
	KleinCoord	kleinTopLeft(-std::tanh(hitbox.width() / 2), std::tanh(hitbox.height() / 2));
	KleinCoord	kleinBotRight(-kleinTopLeft.x(), -kleinTopLeft.y());

	KleinCoord	otherKleinCorner(-std::tanh(other.width() / 2), -std::tanh(other.height() / 2));
	MinkowskiCoord	otherMinkowskiCorner1 = otherKleinCorner.toMinkowski();
	MinkowskiCoord	otherMinkowskiCorner2 = KleinCoord(-otherKleinCorner.x(), otherKleinCorner.y()).toMinkowski();
	MinkowskiCoord	otherMinkowskiCorner3 = KleinCoord(otherKleinCorner.x(), -otherKleinCorner.y()).toMinkowski();
	MinkowskiCoord	otherMinkowskiCorner4 = KleinCoord(-otherKleinCorner.x(), -otherKleinCorner.y()).toMinkowski();
	
	if (isPointInRect(kleinTopLeft, kleinBotRight, otherMinkowskiCorner1.inverseRelativeTo(otherPos).relativeTo(pos).toKlein())
		|| isPointInRect(kleinTopLeft, kleinBotRight, otherMinkowskiCorner2.inverseRelativeTo(otherPos).relativeTo(pos).toKlein())
		|| isPointInRect(kleinTopLeft, kleinBotRight, otherMinkowskiCorner3.inverseRelativeTo(otherPos).relativeTo(pos).toKlein())
		|| isPointInRect(kleinTopLeft, kleinBotRight, otherMinkowskiCorner4.inverseRelativeTo(otherPos).relativeTo(pos).toKlein())
	)
		return true;
	return false;
}

bool	Hitbox::collides(const MinkowskiCoord& pos, const Hitbox& other, const MinkowskiCoord& otherPos) const
{
	if (cornerCollides(*this, pos, other, otherPos) || cornerCollides(other, otherPos, *this, pos))
		return true;
	return false;
}

float	Hitbox::width(void) const { return m_width; }
float	Hitbox::height(void) const { return m_height; }