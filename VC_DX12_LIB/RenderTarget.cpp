#include "stdafx.h"
#include "RenderTarget.h"

RenderTarget::RenderTarget() : Texture(),
m_pRenderTarget(nullptr)
{

}

RenderTarget::~RenderTarget()
{

}

ID3D12Resource* RenderTarget::GetDXRenderTarget()
{
	return m_pRenderTarget;
}

void RenderTarget::CreateRTV(ID3D12Device* pDevice, D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle)
{
	pDevice->CreateRenderTargetView(m_pRenderTarget, nullptr, rtvHandle);
}

void RenderTarget::Begin()
{

}

void RenderTarget::End()
{

}

