#include "stdafx.h"
#include "RenderManager.h"

RenderManager* RenderManager::m_pInst = nullptr;

RenderManager::RenderManager() :
	m_pCommandAllocator(nullptr),
	m_pCommandList(nullptr),
	m_pCommandQueue(nullptr),
	m_pDevice(nullptr),
	m_pFence(nullptr),
	m_pPipelineState(nullptr),
	m_pRtvHeap(nullptr),
	m_pSwapChain(nullptr)
{

}

RenderManager::~RenderManager()
{
	if (m_pInst)
	{
		delete m_pInst;
	}
}

RenderManager& RenderManager::Get()
{
	if (!m_pInst)
	{
		m_pInst = new RenderManager;
	}

	return *m_pInst;
}

void RenderManager::Initialize(HWND hwnd)
{
#if defined(_DEBUG)
	ID3D12Debug* pDebugController = nullptr;
	if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&pDebugController))))
	{
		pDebugController->EnableDebugLayer();
	}
	else
	{
		// Throw an assert here
	}
#endif

	IDXGIFactory4* pFactory = nullptr;
	HRESULT hr = CreateDXGIFactory1(IID_PPV_ARGS(&pFactory));
	if (FAILED(hr))
	{
		// Throw an assert here
	}

	IDXGIAdapter1* pAdapter = nullptr;
	for (UINT i = 0; ; ++i)
	{
		if (DXGI_ERROR_NOT_FOUND == pFactory->EnumAdapters1(i, &pAdapter))
		{
			// No d3d12 adapters found - assert
			break;
		}

		if (SUCCEEDED(D3D12CreateDevice(pAdapter, D3D_FEATURE_LEVEL_11_0, _uuidof(ID3D12Device), (void**)&m_pDevice)))
		{
			break;
		}
		pAdapter->Release();
	}

	D3D12_COMMAND_QUEUE_DESC queueDesc = {};
	queueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
	queueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;

	hr = m_pDevice->CreateCommandQueue(&queueDesc, IID_PPV_ARGS(&m_pCommandQueue));
	if (FAILED(hr))
	{
		// Throw an assert here
	}

	DXGI_SWAP_CHAIN_DESC swapChainDesc = {};
	swapChainDesc.BufferCount = s_frameCount;
	swapChainDesc.BufferDesc.Width = m_screenWidth;
	swapChainDesc.BufferDesc.Height = m_screenHeight;
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
	swapChainDesc.OutputWindow = hwnd;
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.Windowed = TRUE;

	IDXGISwapChain* pSwapChain;
	hr = pFactory->CreateSwapChain(m_pCommandQueue, &swapChainDesc, &pSwapChain);
	if (FAILED(hr))
	{
		// Throw an assert here
	}

	m_pSwapChain = static_cast<IDXGISwapChain3*>(pSwapChain);
	m_frameIndex = m_pSwapChain->GetCurrentBackBufferIndex();

	D3D12_DESCRIPTOR_HEAP_DESC rtvHeapDesc = {};
	rtvHeapDesc.NumDescriptors = s_frameCount;
	rtvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
	rtvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
	hr = m_pDevice->CreateDescriptorHeap(&rtvHeapDesc, IID_PPV_ARGS(&m_pRtvHeap));
	if (FAILED(hr))
	{
		// Throw an assert here
	}

	CD3DX12_CPU_DESCRIPTOR_HANDLE rtvHandle(m_pRtvHeap->GetCPUDescriptorHandleForHeapStart());

	for (UINT i = 0; i < s_frameCount; ++i)
	{
		ID3D12Resource* pFrameBuffer = m_pFrameBuffers[i]->GetDXRenderTarget();
		hr = m_pSwapChain->GetBuffer(i, IID_PPV_ARGS(&pFrameBuffer));
		if (FAILED(hr))
		{
			// Throw an assert here
		}
		m_pFrameBuffers[i]->CreateRTV(m_pDevice, rtvHandle);
		rtvHandle.Offset(1, m_rtvDescriptorSize);
	}

	hr = m_pDevice->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&m_pCommandAllocator));
	if (FAILED(hr))
	{
		// Throw an assert here
	}
}

void RenderManager::Shutdown()
{
	if (m_pCommandAllocator)
	{
		m_pCommandAllocator->Release();
		m_pCommandAllocator = nullptr;
	}

	if (m_pCommandList)
	{
		m_pCommandList->Release();
		m_pCommandList = nullptr;
	}

	if (m_pCommandQueue)
	{
		m_pCommandQueue->Release();
		m_pCommandQueue = nullptr;
	}

	if (m_pDevice)
	{
		m_pDevice->Release();
		m_pDevice = nullptr;
	}

	if (m_pFence)
	{
		m_pFence->Release();
		m_pFence = nullptr;
	}

	if (m_pPipelineState)
	{
		m_pPipelineState->Release();
		m_pPipelineState = nullptr;
	}

	if (m_pRtvHeap)
	{
		m_pRtvHeap->Release();
		m_pRtvHeap = nullptr;
	}

	if (m_pSwapChain)
	{
		m_pSwapChain->Release();
		m_pSwapChain = nullptr;
	}
}

void RenderManager::Render()
{

}

ID3D12Device* RenderManager::GetD3D12Device()
{
	return m_pDevice;
}

