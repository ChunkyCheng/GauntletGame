#pragma once

#include <iostream>
#include "raylib.h"

class	PoincareCoord;

class	MinkowskiCoord
{
	public:
		MinkowskiCoord(float x, float y);
		MinkowskiCoord(const MinkowskiCoord& other) = default;
		MinkowskiCoord&	operator=(const MinkowskiCoord& other) = default;
		~MinkowskiCoord(void) = default;

		PoincareCoord	toPoincare(void) const;
		float			hDist(const MinkowskiCoord& other) const;
		MinkowskiCoord	relativeTo(const MinkowskiCoord& other) const;
		Vector3			relativeRowX(void) const;
		Vector3			relativeRowY(void) const;

		void	moveXHyperbolic(float dist);
		void	moveYHyperbolic(float dist);
		void	moveHyperbolic(float dist, float theta);
		void	setXY(float x, float y);
		float	x(void) const;
		float	y(void) const;
		float	z(void) const;

	private:
		float	m_x;
		float	m_y;
		float	m_z;
};

std::ostream&	operator<<(std::ostream& os, const MinkowskiCoord& m);