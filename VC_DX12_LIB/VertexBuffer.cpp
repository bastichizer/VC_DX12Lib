#include "stdafx.h"
#include "VertexBuffer.h"

VertexBuffer::VertexBuffer() :
	m_pVertexBuffer(nullptr),
	m_pPosition(nullptr),
	m_pColour(nullptr),
	m_pUV0(nullptr),
	m_pUV1(nullptr),
	m_pUV2(nullptr),
	m_pUV3(nullptr),
	m_pNormal(nullptr),
	m_pTangent(nullptr),
	m_pBoneWeights(nullptr),
	m_pBoneIndices(nullptr),
	m_isDynamic(false)
{

}

VertexBuffer::~VertexBuffer()
{
	if (m_pVertexBuffer)
	{
		m_pVertexBuffer->Release();
		m_pVertexBuffer = nullptr;
	}
}

void VertexBuffer::Initialize()
{
	D3D12_INPUT_ELEMENT_DESC tempDescs[9];

	UINT byteOffset = 0;

	tempDescs[0].SemanticName = "POSITION";
	tempDescs[0].SemanticIndex = 0;
	tempDescs[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
	tempDescs[0].InputSlot = 0;
	tempDescs[0].AlignedByteOffset = byteOffset;
	tempDescs[0].InputSlotClass = D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA;
	tempDescs[0].InstanceDataStepRate = 0;
	byteOffset += 12;

	UINT elementIndex = 1;

	if (m_vertexFormat & VertexFormat::Colour)
	{
		tempDescs[elementIndex].SemanticName = "COLOUR";
		tempDescs[elementIndex].SemanticIndex = 0;
		tempDescs[elementIndex].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
		tempDescs[elementIndex].InputSlot = 0;
		tempDescs[elementIndex].AlignedByteOffset = byteOffset;
		tempDescs[elementIndex].InputSlotClass = D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA;
		tempDescs[elementIndex].InstanceDataStepRate = 0;
		byteOffset += 16;
		++elementIndex;
	}

	if (m_vertexFormat & VertexFormat::UV0)
	{
		tempDescs[elementIndex].SemanticName = "TEXCOORD";
		tempDescs[elementIndex].SemanticIndex = 0;
		tempDescs[elementIndex].Format = DXGI_FORMAT_R32G32_FLOAT;
		tempDescs[elementIndex].InputSlot = 0;
		tempDescs[elementIndex].AlignedByteOffset = byteOffset;
		tempDescs[elementIndex].InputSlotClass = D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA;
		tempDescs[elementIndex].InstanceDataStepRate = 0;
		byteOffset += 8;
		++elementIndex;
	}

	if (m_vertexFormat & VertexFormat::UV1)
	{
		tempDescs[elementIndex].SemanticName = "TEXCOORD";
		tempDescs[elementIndex].SemanticIndex = 1;
		tempDescs[elementIndex].Format = DXGI_FORMAT_R32G32_FLOAT;
		tempDescs[elementIndex].InputSlot = 0;
		tempDescs[elementIndex].AlignedByteOffset = byteOffset;
		tempDescs[elementIndex].InputSlotClass = D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA;
		tempDescs[elementIndex].InstanceDataStepRate = 0;
		byteOffset += 8;
		++elementIndex;
	}

	if (m_vertexFormat & VertexFormat::UV2)
	{
		tempDescs[elementIndex].SemanticName = "TEXCOORD";
		tempDescs[elementIndex].SemanticIndex = 2;
		tempDescs[elementIndex].Format = DXGI_FORMAT_R32G32_FLOAT;
		tempDescs[elementIndex].InputSlot = 0;
		tempDescs[elementIndex].AlignedByteOffset = byteOffset;
		tempDescs[elementIndex].InputSlotClass = D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA;
		tempDescs[elementIndex].InstanceDataStepRate = 0;
		byteOffset += 8;
		++elementIndex;
	}

	if (m_vertexFormat & VertexFormat::UV3)
	{
		tempDescs[elementIndex].SemanticName = "TEXCOORD";
		tempDescs[elementIndex].SemanticIndex = 3;
		tempDescs[elementIndex].Format = DXGI_FORMAT_R32G32_FLOAT;
		tempDescs[elementIndex].InputSlot = 0;
		tempDescs[elementIndex].AlignedByteOffset = byteOffset;
		tempDescs[elementIndex].InputSlotClass = D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA;
		tempDescs[elementIndex].InstanceDataStepRate = 0;
		byteOffset += 8;
		++elementIndex;
	}

	if (m_vertexFormat & VertexFormat::Normal)
	{
		tempDescs[elementIndex].SemanticName = "NORMAL";
		tempDescs[elementIndex].SemanticIndex = 0;
		tempDescs[elementIndex].Format = DXGI_FORMAT_R32G32B32_FLOAT;
		tempDescs[elementIndex].InputSlot = 0;
		tempDescs[elementIndex].AlignedByteOffset = byteOffset;
		tempDescs[elementIndex].InputSlotClass = D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA;
		tempDescs[elementIndex].InstanceDataStepRate = 0;
		byteOffset += 12;
		++elementIndex;
	}

	if (m_vertexFormat & VertexFormat::Tangent)
	{
		tempDescs[elementIndex].SemanticName = "TANGENT";
		tempDescs[elementIndex].SemanticIndex = 0;
		tempDescs[elementIndex].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
		tempDescs[elementIndex].InputSlot = 0;
		tempDescs[elementIndex].AlignedByteOffset = byteOffset;
		tempDescs[elementIndex].InputSlotClass = D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA;
		tempDescs[elementIndex].InstanceDataStepRate = 0;
		byteOffset += 16;
		++elementIndex;
	}

	if (m_vertexFormat & VertexFormat::Skinned)
	{
		tempDescs[elementIndex].SemanticName = "WEIGHTS";
		tempDescs[elementIndex].SemanticIndex = 0;
		tempDescs[elementIndex].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
		tempDescs[elementIndex].InputSlot = 0;
		tempDescs[elementIndex].AlignedByteOffset = byteOffset;
		tempDescs[elementIndex].InputSlotClass = D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA;
		tempDescs[elementIndex].InstanceDataStepRate = 0;
		byteOffset += 16;
		++elementIndex;

		tempDescs[elementIndex].SemanticName = "BONES";
		tempDescs[elementIndex].SemanticIndex = 0;
		tempDescs[elementIndex].Format = DXGI_FORMAT_R32G32B32A32_UINT;
		tempDescs[elementIndex].InputSlot = 0;
		tempDescs[elementIndex].AlignedByteOffset = byteOffset;
		tempDescs[elementIndex].InputSlotClass = D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA;
		tempDescs[elementIndex].InstanceDataStepRate = 0;
		byteOffset += 16;
		++elementIndex;
	}


}

