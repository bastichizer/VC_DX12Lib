#pragma once

#ifndef RENDEROBJECT_H
#define RENDEROBJECT_H

#include "Material.h"
#include "VertexBuffer.h"

class RenderObject
{
public:
	RenderObject();
	~RenderObject();

	void Render();
	void SetMaterial(Material* mat)			{ m_pMaterial = mat; }
	Material* GetMaterial()					{ return m_pMaterial; }
	void SetVertexBuffer(VertexBuffer* vb)	{ m_pVertexBuffer = vb; }
	VertexBuffer* GetVertexBuffer()			{ return m_pVertexBuffer; }

private:
	Material*		m_pMaterial;
	VertexBuffer*	m_pVertexBuffer;
};

#endif // RENDEROBJECT_H

