#pragma once

#include <iostream>

class	MinkowskiCoord;

class	KleinCoord
{
	public:
		KleinCoord(float x, float y);
		KleinCoord(const KleinCoord& other) = default;
		KleinCoord&	operator=(const KleinCoord& other) = default;
		~KleinCoord(void) = default;

		MinkowskiCoord	toMinkowski(void) const;

		float	x(void) const;
		float	y(void) const;
		
	private:
		float	m_x;
		float	m_y;
};

std::ostream&	operator<<(std::ostream& os, const KleinCoord& p);