#pragma once

#include "ShaderRaii.hpp"

class	PoincareWarpShader : public ShaderRaii
{
	public:
		PoincareWarpShader(void);
		PoincareWarpShader(const PoincareWarpShader& other) = delete;
		PoincareWarpShader&	operator=(const PoincareWarpShader& other) = delete;
		~PoincareWarpShader(void) = default;

		void	setObjInvFrame(float rowX[3], float rowY[3]) const;
		void	setHalfExtent(float halfExtent) const;
		void	setDiskCenter(float x, float y) const;
		void	setDistRadius(float radius) const;

	private:
		const int	m_objInvFrameRowXLoc;
		const int	m_objInvFrameRowYLoc;
		const int	m_halfExtentLoc;
		const int	m_diskCenterLoc;
		const int	m_diskRadiusLoc;
};

