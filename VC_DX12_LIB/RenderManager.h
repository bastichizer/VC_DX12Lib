#pragma once

#ifndef RENDERMANAGER_H
#define RENDERMANAGER_H

#include <d3d12.h>
#include "d3dx12.h"
#include <dxgi1_4.h>
#include "RenderTarget.h"

class RenderManager
{
public:
	~RenderManager();

	static RenderManager& Get();

	void Initialize(HWND hwnd);
	void Shutdown();

	void Render();

	ID3D12Device* GetD3D12Device();

private:

	RenderManager();

	static RenderManager*		m_pInst;

	static const UINT			s_frameCount = 2;

	D3D12_VIEWPORT				m_viewport;
	D3D12_RECT					m_scissorRect;

	IDXGISwapChain3*			m_pSwapChain;
	ID3D12Device*				m_pDevice;
	ID3D12CommandAllocator*		m_pCommandAllocator;
	ID3D12CommandQueue*			m_pCommandQueue;
	ID3D12DescriptorHeap*		m_pRtvHeap; // render target view?  Goes in RenderTarget?
	ID3D12PipelineState*		m_pPipelineState;
	ID3D12GraphicsCommandList*	m_pCommandList;
	UINT						m_rtvDescriptorSize; // render target view?  Goes in RenderTarget?

	UINT						m_frameIndex;
	HANDLE						m_fenceEvent;
	ID3D12Fence*				m_pFence;
	UINT64						m_fenceValue;

	UINT						m_screenWidth;
	UINT						m_screenHeight;

	RenderTarget*				m_pFrameBuffers[s_frameCount];

};

#endif //RENDERMANAGER_H
