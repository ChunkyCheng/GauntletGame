#pragma once

#include <iostream>
#include "PoincareCoord.hpp"

class	MinkowskiCoord
{
	public:
		MinkowskiCoord(float x, float y);
		MinkowskiCoord(const MinkowskiCoord& other) = default;
		MinkowskiCoord&	operator=(const MinkowskiCoord& other) = default;
		~MinkowskiCoord(void) = default;

		PoincareCoord	toPoincare(void) const;

		void	setX(float x);
		void	setY(float y);
		void	setZ(float z);
		float	x(void) const;
		float	y(void) const;
		float	z(void) const;

	private:
		float	m_x;
		float	m_y;
		float	m_z;
};

std::ostream&	operator<<(std::ostream& os, const MinkowskiCoord& m);