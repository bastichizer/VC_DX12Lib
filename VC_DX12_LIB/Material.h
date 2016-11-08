#pragma once

#ifndef MATERIAL_H
#define MATERIAL_H

#include "Shader.h"

class Material
{
public:
	Material();
	~Material();

	void SetShader(Shader* shader) { m_shader = shader; }
	Shader* GetShader() { return m_shader; }

private:
	Shader* m_shader;
};

#endif // !MATERIAL_H
