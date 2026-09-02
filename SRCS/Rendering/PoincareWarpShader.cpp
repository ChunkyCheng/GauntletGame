#include "PoincareWarpShader.hpp"

PoincareWarpShader::PoincareWarpShader(void)
	: ShaderRaii(nullptr, "SRCS/Shaders/PoincareWarp.frag")
	, m_objInvFrameRowXLoc(GetShaderLocation(**this, "objInvFrameRowX"))
	, m_objInvFrameRowYLoc(GetShaderLocation(**this, "objInvFrameRowY"))
	, m_extentLoc(GetShaderLocation(**this, "extent"))
	, m_diskCenterLoc(GetShaderLocation(**this, "diskCenter"))
	, m_diskRadiusLoc(GetShaderLocation(**this, "diskRadius"))
	, m_drawModeLoc(GetShaderLocation(**this, "drawMode"))
	, m_textureOffsetLoc(GetShaderLocation(**this, "textureOffset"))
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
void	PoincareWarpShader::setExtent(Vector2 extent) const
{
	SetShaderValue(**this, m_extentLoc, &extent, SHADER_UNIFORM_VEC2);
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

void	PoincareWarpShader::setDrawMode(DrawMode drawMode) const
{
	SetShaderValue(**this, m_drawModeLoc, &drawMode, SHADER_UNIFORM_INT);
}

void	PoincareWarpShader::setTextureOffset(Vector2 textureOffset) const
{
	SetShaderValue(**this, m_textureOffsetLoc, &textureOffset, SHADER_UNIFORM_VEC2);
}