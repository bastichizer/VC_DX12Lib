#include "stdafx.h"
#include "Shader.h"
#include "RenderManager.h"
#include <d3dcompiler.h>

Shader::Shader() :
m_pError(nullptr),
m_pRootSignature(nullptr),
m_pPixelShader(nullptr),
m_pVertexShader(nullptr)
{

}

Shader::~Shader()
{
	if (m_pError)
	{
		m_pError->Release();
		m_pError = nullptr;
	}

	if (m_pRootSignature)
	{
		m_pRootSignature->Release();
		m_pRootSignature = nullptr;
	}

	if (m_pPixelShader)
	{
		m_pPixelShader->Release();
		m_pPixelShader = nullptr;
	}

	if (m_pVertexShader)
	{
		m_pVertexShader->Release();
		m_pVertexShader = nullptr;
	}
}

void Shader::LoadShader(char* filename)
{
	CD3DX12_ROOT_SIGNATURE_DESC rootSignatureDesc;
	rootSignatureDesc.Init(0, nullptr, 0, nullptr, D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT);
	ID3DBlob* tempSignature = nullptr;
	HRESULT hr = D3D12SerializeRootSignature(&rootSignatureDesc, D3D_ROOT_SIGNATURE_VERSION_1, &tempSignature, &m_pError);
	if (FAILED(hr))
	{
		// Throw assert here
	}
	hr = RenderManager::Get().GetD3D12Device()->CreateRootSignature(0, tempSignature->GetBufferPointer(), tempSignature->GetBufferSize(), IID_PPV_ARGS(&m_pRootSignature));
	if (FAILED(hr))
	{
		// Throw assert here
	}

#if defined(_DEBUG)
	UINT compileFlags = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
#else
	UINT compileFlags = 0;
#endif

	wchar_t path[128];
	mbstowcs(path, filename, strlen(filename) + 1);
	LPWSTR pPath = path;
	hr = D3DCompileFromFile(pPath, nullptr, nullptr, "VSMain", "vs_5_0", compileFlags, 0, &m_pVertexShader, nullptr);
	if (FAILED(hr))
	{
		// Throw assert here
	}
	hr = D3DCompileFromFile(pPath, nullptr, nullptr, "PSMain", "ps_5_0", compileFlags, 0, &m_pPixelShader, nullptr);
	if (FAILED(hr))
	{
		// Throw assert here
	}


}

