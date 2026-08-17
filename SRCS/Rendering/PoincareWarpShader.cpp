#include "PoincareWarpShader.hpp"
#include "raylib.h"

PoincareWarpShader::PoincareWarpShader(void)
	: ShaderRaii(nullptr, "SRCS/Shaders/PoincareWarp.frag")
	, m_objInvFrameRowXLoc(GetShaderLocation(**this, "objInvFrameRowX"))
	, m_objInvFrameRowYLoc(GetShaderLocation(**this, "objInvFrameRowY"))
	, m_halfExtentLoc(GetShaderLocation(**this, "halfExtentLoc"))
	, m_diskCenterLoc(GetShaderLocation(**this, "diskCenterLoc"))
	, m_diskRadiusLoc(GetShaderLocation(**this, "diskRadiusLoc"))
{
}

void	PoincareWarpShader::setObjInvFrame(float rowX[3], float rowY[3]) const
{
	SetShaderValue(**this, m_objInvFrameRowXLoc, rowX, SHADER_UNIFORM_VEC3);
	SetShaderValue(**this, m_objInvFrameRowYLoc, rowY, SHADER_UNIFORM_VEC3);
	
}
void	PoincareWarpShader::setHalfExtent(float halfExtent) const
{
	SetShaderValue(**this, m_halfExtentLoc, &halfExtent, SHADER_UNIFORM_FLOAT);
}

void	PoincareWarpShader::setDiskCenter(float x, float y) const
{
	float	diskCenter[2] = {x, y};

	SetShaderValue(**this, m_diskCenterLoc, diskCenter, SHADER_UNIFORM_VEC2);
}

void	PoincareWarpShader::setDistRadius(float radius) const
{
	SetShaderValue(**this, m_halfExtentLoc, &radius, SHADER_UNIFORM_FLOAT);
}

