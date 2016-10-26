#pragma once

#ifndef TEXTURE_H
#define TEXTURE_H

#include <d3d12.h>

class Texture
{
public:
	Texture();
	~Texture();

	void SetSize(UINT32 width, UINT32 height);

private:
	UINT32 m_width;
	UINT32 m_height;
};

#endif // TEXTURE_H

