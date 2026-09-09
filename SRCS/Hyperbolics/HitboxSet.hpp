#pragma once

#include <array>
#include "Hitbox.hpp"
#include "MinkowskiCoord.hpp"

template<std::size_t N>
class	HitboxSet
{
	public:
		HitboxSet(void);
		HitboxSet(const HitboxSet& other);
		HitboxSet&	operator=(const HitboxSet& other);
		~HitboxSet(void);

		template<std::size_t M>
		bool	collides(const MinkowskiCoord& pos, const HitboxSet<M>& other, const MinkowskiCoord& otherPos);

	private:
		std::array<Hitbox, N>	m_hitboxes;
};

template<std::size_t N, std::size_t M>
bool	HitboxSet<N>::collides(const MinkowskiCoord& pos, const HitboxSet<M>& other, const MinkowskiCoord& otherPos)
{
	for (const auto& hitbox : m_hitboxes)
	{
		for (const auto& otherHitbox : other.m_hitboxes)
		{
			if (hitbox.collides(pos, otherHitbox, otherPos))
				return true;
		}
	}
	return false;
}
