#include "PoincareCoord.hpp"
#include <iomanip>
#include <cassert>

PoincareCoord::PoincareCoord(float x, float y)
	: m_x(x)
	, m_y(y)
{
	assert(m_x >= -1);
	assert(m_x <= 1);
	assert(m_y >= -1);
	assert(m_y <= 1);
}

float	PoincareCoord::x(void) const { return m_x; }
float	PoincareCoord::y(void) const { return m_y; }


std::ostream&	operator<<(std::ostream& os, const PoincareCoord& p)
{
	os << std::fixed << std::setprecision(3);
	os << "(" << p.x() << ", " << p.y() << ")";
	return os;
}
