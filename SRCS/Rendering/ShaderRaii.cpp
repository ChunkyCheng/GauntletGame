#include "ShaderRaii.hpp"

ShaderRaii::ShaderRaii(const char* vsFileName, const char* fsFileName)
	: m_shader(LoadShader(vsFileName, fsFileName))
{
}

ShaderRaii::~ShaderRaii(void)
{
	UnloadShader(m_shader);
}

const Shader&	ShaderRaii::operator*(void) const
{
	return m_shader;	
}

const Shader&	ShaderRaii::operator->(void) const
{
	return m_shader;
}