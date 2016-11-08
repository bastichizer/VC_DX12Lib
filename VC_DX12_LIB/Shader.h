#pragma once

#ifndef SHADER_H
#define SHADER_H

#include <d3d12.h>
#include "d3dx12.h"
#include <dxgi1_4.h>

class Shader
{
public:
	Shader();
	~Shader();

	void LoadShader(char* filename);
	ID3D12RootSignature* GetRootSignature() { return m_pRootSignature; }
	ID3DBlob* GetVertexShader() { return m_pVertexShader; }
	ID3DBlob* GetPixelShader() { return m_pPixelShader; }

private:
	ID3D12RootSignature*		m_pRootSignature;
	ID3DBlob*					m_pError;
	ID3DBlob*					m_pVertexShader;
	ID3DBlob*					m_pPixelShader;
};

#endif // !SHADER_H
