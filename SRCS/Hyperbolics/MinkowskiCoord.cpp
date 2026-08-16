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

float	MinkowskiCoord::x(void) const { return m_x; }
float	MinkowskiCoord::y(void) const { return m_y; }
float	MinkowskiCoord::z(void) const { return m_z; }

std::ostream&	operator<<(std::ostream& os, const MinkowskiCoord& m)
{
	os << std::fixed << std::setprecision(3);
	os << "(" << m.x() << ", " << m.y() << ", " << m.z() << ")";
	return os;
}