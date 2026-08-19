#include "PoincareCoord.hpp"
#include <iomanip>
#include <cassert>
#include "MinkowskiCoord.hpp"

PoincareCoord::PoincareCoord(float x, float y)
	: m_x(x)
	, m_y(y)
{
	assert(m_x >= -1);
	assert(m_x <= 1);
	assert(m_y >= -1);
	assert(m_y <= 1);
}

MinkowskiCoord	PoincareCoord::toMinkowski(void) const
{
	float denom = 1.0 - (m_x * m_x + m_y * m_y);

	if (denom == 0)
		return MinkowskiCoord(m_x * 1000, m_y * 1000);
	return MinkowskiCoord(2.0 * m_x / denom, 2.0 * m_y / denom);
}

float	PoincareCoord::x(void) const { return m_x; }
float	PoincareCoord::y(void) const { return m_y; }

std::ostream&	operator<<(std::ostream& os, const PoincareCoord& p)
{
	os << std::fixed << std::setprecision(3);
	os << "(" << p.x() << ", " << p.y() << ")";
	return os;
}
