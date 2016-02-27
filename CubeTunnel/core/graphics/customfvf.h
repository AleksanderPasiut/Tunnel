#pragma once

#include <d3d9.h>

#define CUSTOMFVF_TYPE D3DFVF_XYZ | D3DFVF_NORMAL
struct CUSTOMFVF
{
	float x;
	float y;
	float z;
	D3DVECTOR normal;
};
