#include "ShaderRaii.hpp"
#include "raylib.h"

ShaderRaii::ShaderRaii(const char* vsFileName, const char* fsFileName)
{
	m_shaderPtr = new Shader(LoadShader(vsFileName, fsFileName));
}

ShaderRaii::~ShaderRaii(void)
{
	UnloadShader(*m_shaderPtr);
	delete m_shaderPtr;
}

const Shader&	ShaderRaii::operator*(void) const
{
	return *m_shaderPtr;	
}

const Shader&	ShaderRaii::operator->(void) const
{
	return *m_shaderPtr;	
}