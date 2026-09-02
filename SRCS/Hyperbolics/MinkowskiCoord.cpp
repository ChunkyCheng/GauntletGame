#include "MinkowskiCoord.hpp"
#include <iomanip>
#include <cmath>
#include "PoincareCoord.hpp"

MinkowskiCoord::MinkowskiCoord(float x, float y)
	: m_x(x)
	, m_y(y)
	, m_z(std::sqrt(x * x + y * y + 1))
{
}

PoincareCoord	MinkowskiCoord::toPoincare(void) const
{
	return PoincareCoord(m_x / (m_z + 1), m_y / (m_z + 1));
}

float	MinkowskiCoord::hDist(const MinkowskiCoord& other) const
{
	return std::acosh(m_z * other.m_z - m_x * other.m_x - m_y * other.m_y);
}

//Finds the first 2 rows of a matrix X such that X(other) = (0, 0, 1)
//X is then used on this x and y to produce the relative Minkowski coordinate
//Preserves the x^2 + y^2 + 1 = z^2 relationship
MinkowskiCoord	MinkowskiCoord::relativeTo(const MinkowskiCoord& other) const
{
	Vector3	invRowX = other.relativeRowX();
	Vector3	invRowY = other.relativeRowY();

	float	x = invRowX.x * m_x + invRowX.y * m_y + invRowX.z * m_z;
	float	y = invRowY.x * m_x + invRowY.y * m_y + invRowY.z * m_z;

	return MinkowskiCoord(x, y);
}

Vector3	MinkowskiCoord::relativeRowX(void) const
{
	return {
		1 + m_x * m_x / (m_z + 1),
		m_x * m_y / (m_z + 1),
		-m_x
	};	
}

Vector3	MinkowskiCoord::relativeRowY(void) const
{
	return {
		m_x * m_y / (m_z + 1),
		1 + m_y * m_y / (m_z + 1),
		-m_y
	};
}

void	MinkowskiCoord::moveXHyperbolic(float dist)
{
	m_x = std::cosh(dist) * m_x + std::sinh(dist) * m_z;
	m_z = std::sqrt(m_x * m_x + m_y * m_y + 1);
}

void	MinkowskiCoord::moveYHyperbolic(float dist)
{
	m_y = std::cosh(dist) * m_y + std::sinh(dist) * m_z;
	m_z = std::sqrt(m_x * m_x + m_y * m_y + 1);
}

void	MinkowskiCoord::moveHyperbolic(float dist, float theta)
{
	float	sinhD = std::sinh(dist);
	float	RQ[3] = {sinhD * std::cos(theta), sinhD * std::sin(theta), std::cosh(dist)};
	float	invR1[3] = {
		1 + m_x * m_x / (m_z + 1),
		m_x * m_y / (m_z + 1),
		m_x
	};
	float	invR2[3] = {
		invR1[1],
		1 + m_y * m_y / (m_z + 1),
		m_y
	};

	m_x = RQ[0] * invR1[0] + RQ[1] * invR1[1] + RQ[2] * invR1[2];
	m_y = RQ[0] * invR2[0] + RQ[1] * invR2[1] + RQ[2] * invR2[2];
	m_z = std::sqrt(m_x * m_x + m_y * m_y + 1);
}

void	MinkowskiCoord::setXY(float x, float y)
{
	m_x = x;
	m_y = y;
	m_z = std::sqrt(x * x + y * y + 1);
}

float	MinkowskiCoord::x(void) const { return m_x; }
float	MinkowskiCoord::y(void) const { return m_y; }
float	MinkowskiCoord::z(void) const { return m_z; }

std::ostream&	operator<<(std::ostream& os, const MinkowskiCoord& m)
{
	os << std::fixed << std::setprecision(3);
	os << "(" << m.x() << ", " << m.y() << ", " << m.z() << ")";
	return os;
}