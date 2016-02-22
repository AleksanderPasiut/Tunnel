#include "tunnel.h"

TUNNEL::TUNNEL(GRAPHICS& in_graphics) : 
	graphics(in_graphics)
{
	CreateBoundingCube();
}

TUNNEL::~TUNNEL() noexcept
{
	bounding_cube->Release();
}

void TUNNEL::Draw() noexcept
{
	IDirect3DDevice9& dev = *graphics.RetDevice();

	dev.SetFVF(CUSTOMFVF_TYPE);

	DrawBoundingCube();
}