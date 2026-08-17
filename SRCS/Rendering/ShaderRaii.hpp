#pragma once

#include "raylib.h"

class	Shader;

class	ShaderRaii
{
	protected:
		ShaderRaii(const char* vsFileName, const char* fsFileName);
		ShaderRaii(const ShaderRaii& other) = delete;
		ShaderRaii&	operator=(const ShaderRaii& other) = delete;
	public:
		virtual ~ShaderRaii(void);

	public:
		const Shader&	operator*(void) const;
		const Shader&	operator->(void) const;

	protected:
		Shader	m_shader;
};

