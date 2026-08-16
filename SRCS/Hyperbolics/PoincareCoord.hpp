#pragma once

#include <iostream>

class	PoincareCoord
{
	public:
		PoincareCoord(float x, float y);
		PoincareCoord(const PoincareCoord& other) = default;
		PoincareCoord&	operator=(const PoincareCoord& other) = default;
		~PoincareCoord(void) = default;

		void	setX(float x);
		void	setY(float y);
		float	x(void) const;
		float	y(void) const;

	private:
		float	m_x;
		float	m_y;
};

std::ostream&	operator<<(std::ostream& os, const PoincareCoord& p);