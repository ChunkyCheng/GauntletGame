#include "PoincareWarpShader.hpp"

PoincareWarpShader::PoincareWarpShader(void)
	: ShaderRaii(nullptr, "SRCS/Shaders/PoincareWarp.frag")
	, m_objInvFrameRowXLoc(GetShaderLocation(**this, "objInvFrameRowX"))
	, m_objInvFrameRowYLoc(GetShaderLocation(**this, "objInvFrameRowY"))
	, m_halfExtentLoc(GetShaderLocation(**this, "halfExtent"))
	, m_diskCenterLoc(GetShaderLocation(**this, "diskCenter"))
	, m_diskRadiusLoc(GetShaderLocation(**this, "diskRadius"))
{
}

PoincareWarpShader::~PoincareWarpShader(void)
{
}

void	PoincareWarpShader::setObjInvFrame(Vector3 rowX, Vector3 rowY) const
{
	float	arrX[3] = {rowX.x, rowX.y, rowX.z};
	float	arrY[3] = {rowY.x, rowY.y, rowY.z};

	SetShaderValue(**this, m_objInvFrameRowXLoc, arrX, SHADER_UNIFORM_VEC3);
	SetShaderValue(**this, m_objInvFrameRowYLoc, arrY, SHADER_UNIFORM_VEC3);
	
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

void	PoincareWarpShader::setDiskRadius(float radius) const
{
	SetShaderValue(**this, m_diskRadiusLoc, &radius, SHADER_UNIFORM_FLOAT);
}

