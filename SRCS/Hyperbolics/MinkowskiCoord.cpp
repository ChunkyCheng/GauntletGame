#include "MinkowskiCoord.hpp"
#include <iomanip>
#include <cmath>

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
MinkowskiCoord	MinkowskiCoord::relativeTo(const MinkowskiCoord& other) const
{
	float	row1[3] = {
		1 + other.m_x * other.m_x / (other.m_z + 1),
		other.m_x * other.m_y / (other.m_z + 1),
		-other.m_x
	};
	float	row2[3] = {
		other.m_x * other.m_y / (other.m_z + 1),
		1 + other.m_y * other.m_y / (other.m_z + 1),
		-other.m_y
	};

	float	x = row1[0] * m_x + row1[1] * m_y + row1[2] * m_z;
	float	y = row2[0] * m_x + row2[1] * m_y + row2[2] * m_z;

	return MinkowskiCoord(x, y);
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