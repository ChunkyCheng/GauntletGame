#include "KleinCoord.hpp"
#include <iomanip>
#include <cassert>
#include <cmath>
#include "MinkowskiCoord.hpp"

KleinCoord::KleinCoord(float x, float y)
	: m_x(x)
	, m_y(y)
{
	assert(m_x >= -1);
	assert(m_x <= 1);
	assert(m_y >= -1);
	assert(m_y <= 1);
}

MinkowskiCoord	KleinCoord::toMinkowski(void) const
{
	float denom = std::sqrt(1 - m_x * m_x - m_y * m_y);

	if (denom == 0)
		return MinkowskiCoord(m_x * 1000, m_y * 1000);
	return MinkowskiCoord(m_x / denom, m_y / denom);
}

float	KleinCoord::x(void) const { return m_x; }
float	KleinCoord::y(void) const { return m_y; }

std::ostream&	operator<<(std::ostream& os, const KleinCoord& p)
{
	os << std::fixed << std::setprecision(3);
	os << "(" << p.x() << ", " << p.y() << ")";
	return os;
}
