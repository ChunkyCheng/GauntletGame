#pragma once

class	MinkowskiCoord;

class	Hitbox
{
	public:
		Hitbox(float width, float height);
		Hitbox(const Hitbox& other) = default;
		Hitbox&	operator=(const Hitbox& other) = default;
		~Hitbox(void) = default;

		bool	collides(const MinkowskiCoord& pos, const Hitbox& other, const MinkowskiCoord& otherPos) const;

		float	width(void) const;
		float	height(void) const;
		
	private:
		const float	m_width;
		const float	m_height;
};

