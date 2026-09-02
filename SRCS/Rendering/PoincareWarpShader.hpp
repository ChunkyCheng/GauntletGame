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

		enum	DrawMode
		{
			textured,
			circle,
			rectangle
		};

		void	setObjInvFrame(Vector3 rowX, Vector3 rowY) const;
		void	setExtent(Vector2 extent) const;
		void	setDiskCenter(float x, float y) const;
		void	setDiskRadius(float radius) const;
		void	setDrawMode(DrawMode drawMode) const;
		void	setTextureOffset(Vector2 textureOffset) const;

	private:
		const int	m_objInvFrameRowXLoc;
		const int	m_objInvFrameRowYLoc;
		const int	m_extentLoc;
		const int	m_diskCenterLoc;
		const int	m_diskRadiusLoc;
		const int	m_drawModeLoc;
		const int	m_textureOffsetLoc;
};

