#pragma once

class	MinkowskiCoord;

class	Hitbox
{
	public:
		Hitbox(float width, float height);
		Hitbox(const Hitbox& other);
		Hitbox&	operator=(const Hitbox& other);
		~Hitbox(void);

		bool	collides(const MinkowskiCoord& pos, const Hitbox& other, const MinkowskiCoord& otherPos) const;

		float	width(void) const;
		float	height(void) const;
		
	private:
		const float	m_width;
		const float	m_height;
};

