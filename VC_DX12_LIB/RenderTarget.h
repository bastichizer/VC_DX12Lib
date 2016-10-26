#pragma once

#ifndef RENDERTARGET_H
#define RENDERTARGET_H

#include "Texture.h"

class RenderTarget : public Texture
{
public:
	RenderTarget();
	~RenderTarget();

	virtual ID3D12Resource* GetDXRenderTarget();
	virtual void CreateRTV(ID3D12Device* pDevice, D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle);

	virtual void Begin();
	virtual void End();

private:

	ID3D12Resource* m_pRenderTarget;
};

#endif // RENDERTARGET_H

