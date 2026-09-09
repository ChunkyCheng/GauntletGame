#include "MinkowskiCoord.hpp"
#include <iomanip>
#include <cmath>
#include "PoincareCoord.hpp"
#include "KleinCoord.hpp"

MinkowskiCoord::MinkowskiCoord(float x, float y)
	: m_vector({x, y, std::sqrt(x * x + y * y + 1)})
{}

PoincareCoord	MinkowskiCoord::toPoincare(void) const
{
	return PoincareCoord(x() / (z() + 1), y() / (z() + 1));
}

KleinCoord	MinkowskiCoord::toKlein(void) const
{
	return KleinCoord(x() / z(), y() / z());
}

float	MinkowskiCoord::hDist(const MinkowskiCoord& other) const
{
	return std::acosh(z() * other.z() - x() * other.x() - y() * other.y());
}

//Finds the first 2 rows of a matrix X such that X(other) = (0, 0, 1)
//X is then used on this x and y to produce the relative Minkowski coordinate
//Preserves the x^2 + y^2 + 1 = z^2 relationship
MinkowskiCoord	MinkowskiCoord::relativeTo(const MinkowskiCoord& other) const
{
	Vector3	rowX = other.relativeRowX();
	Vector3	rowY = other.relativeRowY();

	float	newX = rowX.x * x() + rowX.y * y() + rowX.z * z();
	float	newY = rowY.x * x() + rowY.y * y() + rowY.z * z();

	return MinkowskiCoord(newX, newY);
}

MinkowskiCoord	MinkowskiCoord::inverseRelativeTo(const MinkowskiCoord& other) const
{
	Vector3	rowX = other.invRelativeRowX();
	Vector3	rowY = other.invRelativeRowY();

	float	newX = rowX.x * x() + rowX.y * y() + rowX.z * z();
	float	newY = rowY.x * x() + rowY.y * y() + rowY.z * z();
	return MinkowskiCoord(newX, newY);
}

void	MinkowskiCoord::moveXHyperbolic(float dist)
{
	m_vector.x = std::cosh(dist) * x() + std::sinh(dist) * z();
	m_vector.z = std::sqrt(x() * x() + y() * y() + 1);
}

void	MinkowskiCoord::moveYHyperbolic(float dist)
{
	m_vector.y = std::cosh(dist) * y() + std::sinh(dist) * z();
	m_vector.z = std::sqrt(x() * x() + y() * y() + 1);
}

void	MinkowskiCoord::moveHyperbolic(float dist, float theta)
{
	float	sinhD = std::sinh(dist);
	float	RQ[3] = {sinhD * std::cos(theta), sinhD * std::sin(theta), std::cosh(dist)};
	Vector3	invRowX = invRelativeRowX();
	Vector3 invRowY = invRelativeRowY();

	m_vector.x = RQ[0] * invRowX.x + RQ[1] * invRowX.y + RQ[2] * invRowX.z;
	m_vector.y = RQ[0] * invRowY.x + RQ[1] * invRowY.y + RQ[2] * invRowY.z;
	m_vector.z = std::sqrt(x() * x() + y() * y() + 1);
}

Vector3	MinkowskiCoord::relativeRowX(void) const
{
	return {
		1 + x() * x() / (z() + 1),
		x() * y() / (z() + 1),
		-x()
	};	
}

Vector3	MinkowskiCoord::relativeRowY(void) const
{
	return {
		x() * y() / (z() + 1),
		1 + y() * y() / (z() + 1),
		-y()
	};
}

Vector3	MinkowskiCoord::invRelativeRowX(void) const
{
	return {
		1 + x() * x() / (z() + 1),
		x() * y() / (z() + 1),
		x()
	};	
}

Vector3	MinkowskiCoord::invRelativeRowY(void) const
{
	return {
		x() * y() / (z() + 1),
		1 + y() * y() / (z() + 1),
		y()
	};
}

void	MinkowskiCoord::setXY(float x, float y)
{
	m_vector.x = x;
	m_vector.y = y;
	m_vector.z = std::sqrt(x * x + y * y + 1);
}

float			MinkowskiCoord::x(void) const { return m_vector.x; }
float			MinkowskiCoord::y(void) const { return m_vector.y; }
float			MinkowskiCoord::z(void) const { return m_vector.z; }
const Vector3&	MinkowskiCoord::vector(void) const { return m_vector; }

std::ostream&	operator<<(std::ostream& os, const MinkowskiCoord& m)
{
	os << std::fixed << std::setprecision(3);
	os << "(" << m.x() << ", " << m.y() << ", " << m.z() << ")";
	return os;
}