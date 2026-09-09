#include "Hitbox.hpp"
#include <iostream>
#include <cmath>
#include <array>
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

Vector3	crossProduct(const MinkowskiCoord& a, const MinkowskiCoord& b)
{
	return {
		a.y() * b.z() - a.z() * b.y(),
		a.z() * b.x() - a.x() * b.z(),
		a.x() * b.y() - a.y() * b.x()
	};
}

Vector3	crossProduct(const Vector3& a, const Vector3& b)
{
	return {
		a.y * b.z - a.z * b.y,
		a.z * b.x - a.x * b.z,
		a.x * b.y - a.y * b.x
	};
}

float	innerProduct(const MinkowskiCoord& a, const MinkowskiCoord& b)
{
	return a.z() * b.z() - a.y() * b.y() - a.x() * b.x();
}

bool	geodesicIntersects(const MinkowskiCoord& p1, const MinkowskiCoord& p2, const MinkowskiCoord& q1, const MinkowskiCoord q2)
{
	Vector3	crossProductP = crossProduct(p1, p2);
	Vector3 crossProductQ = crossProduct(q1, q2);
	Vector3	pxq = crossProduct(crossProductP, crossProductQ);
	float	pxqInnerProduct = pxq.z * pxq.z - pxq.y * pxq.y - pxq.x * pxq.x;

	if (pxqInnerProduct <= 0)
		return false;
	
	float	pxqRootInnerProduct = std::sqrt(pxqInnerProduct);
	if (pxq.z < 0)
		pxqRootInnerProduct *= -1;
	MinkowskiCoord intersection(pxq.x / pxqRootInnerProduct, pxq.y / pxqRootInnerProduct);

	if (innerProduct(intersection, p1) < innerProduct(p1, p2) && innerProduct(intersection, p2) < innerProduct(p1, p2)
		&& (innerProduct(intersection, q1) < innerProduct(q1, q2) && innerProduct(intersection, q2) < innerProduct(q1, q2)))
		return true;
	return false;
}

bool	Hitbox::collides(const MinkowskiCoord& pos, const Hitbox& other, const MinkowskiCoord& otherPos) const
{
	KleinCoord	kleinTopRight(std::tanh(width() / 2), std::tanh(height() / 2));

	KleinCoord	otherKleinCorner(std::tanh(other.width() / 2), std::tanh(other.height() / 2));
	MinkowskiCoord	otherMinkowskiCorner1 = otherKleinCorner.toMinkowski();
	MinkowskiCoord	otherMinkowskiCorner2 = KleinCoord(-otherKleinCorner.x(), otherKleinCorner.y()).toMinkowski();
	MinkowskiCoord	otherMinkowskiCorner3 = KleinCoord(-otherKleinCorner.x(), -otherKleinCorner.y()).toMinkowski();
	MinkowskiCoord	otherMinkowskiCorner4 = KleinCoord(otherKleinCorner.x(), -otherKleinCorner.y()).toMinkowski();

	std::array<MinkowskiCoord, 4>	corners = {
		kleinTopRight.toMinkowski(),
		KleinCoord(-kleinTopRight.x(), kleinTopRight.y()).toMinkowski(),
		KleinCoord(-kleinTopRight.x(), -kleinTopRight.y()).toMinkowski(),
		KleinCoord(kleinTopRight.x(), -kleinTopRight.y()).toMinkowski()
	};
	
	std::array<MinkowskiCoord, 4>	otherCorners = {
		otherMinkowskiCorner1.inverseRelativeTo(otherPos).relativeTo(pos),
		otherMinkowskiCorner2.inverseRelativeTo(otherPos).relativeTo(pos),
		otherMinkowskiCorner3.inverseRelativeTo(otherPos).relativeTo(pos),
		otherMinkowskiCorner4.inverseRelativeTo(otherPos).relativeTo(pos)
	
	};

	for (size_t i = 0; i < 4; ++i)
	{
		for (size_t j = 0; j < 4; ++j)
		{
			if (geodesicIntersects(corners[i], corners[(i + 1) % 4], otherCorners[j], otherCorners[(j + 1) % 4]))
				return true;
		}
	}
	if (isPointInRect(corners[1].toKlein(), corners[3].toKlein(), otherCorners[0].toKlein())
		|| isPointInRect(otherCorners[1].toKlein(), otherCorners[3].toKlein(), corners[0].toKlein()))
		return true;
	return false;
}

float	Hitbox::width(void) const { return m_width; }
float	Hitbox::height(void) const { return m_height; }