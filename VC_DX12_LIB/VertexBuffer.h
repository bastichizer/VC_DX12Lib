#pragma once

#ifndef VERTEXBUFFER_H
#define VERTEXBUFFER_H

#include <DirectXMath.h>
using namespace DirectX;
#include <d3d12.h>

class VertexBuffer
{
public:
	VertexBuffer();
	~VertexBuffer();

	enum VertexFormat
	{
		Colour	= 1 << 0,
		UV0		= 1 << 1,
		UV1		= 1 << 2,
		UV2		= 1 << 3,
		UV3		= 1 << 4,
		Normal	= 1 << 5,
		Tangent = 1 << 6,
		Skinned = 1 << 7
	};

	void Initialize();

private:
	ID3D12Resource*						m_pVertexBuffer;
	D3D12_VERSIONED_ROOT_SIGNATURE_DESC m_vertexBufferView;

	VertexFormat m_vertexFormat;

	XMFLOAT3*	m_pPosition;
	XMFLOAT4*	m_pColour;
	XMFLOAT2*	m_pUV0;
	XMFLOAT2*	m_pUV1;
	XMFLOAT2*	m_pUV2;
	XMFLOAT2*	m_pUV3;
	XMFLOAT3*	m_pNormal;
	XMFLOAT4*	m_pTangent;
	XMFLOAT4*	m_pBoneWeights;
	XMUINT4*	m_pBoneIndices;

	bool		m_isDynamic;
};

#endif // VERTEXBUFFER_H

