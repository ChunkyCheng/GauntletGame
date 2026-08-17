#pragma once

#include "ShaderRaii.hpp"
#include "raylib.h"

class	PoincareWarpShader : public ShaderRaii
{
	public:
		PoincareWarpShader(void);
		PoincareWarpShader(const PoincareWarpShader& other) = delete;
		PoincareWarpShader&	operator=(const PoincareWarpShader& other) = delete;
		~PoincareWarpShader(void);

		void	setObjInvFrame(Vector3 rowX, Vector3 rowY) const;
		void	setHalfExtent(float halfExtent) const;
		void	setDiskCenter(float x, float y) const;
		void	setDiskRadius(float radius) const;

	private:
		const int	m_objInvFrameRowXLoc;
		const int	m_objInvFrameRowYLoc;
		const int	m_halfExtentLoc;
		const int	m_diskCenterLoc;
		const int	m_diskRadiusLoc;
};

