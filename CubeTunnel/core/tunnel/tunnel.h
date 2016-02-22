#pragma once

#include "..\\graphics\\graphics.h"

class TUNNEL
{
protected:
	GRAPHICS& graphics;

	IDirect3DVertexBuffer9* bounding_cube;

	void CreateBoundingCube() noexcept;
	void DrawBoundingCube() noexcept;


public:
	TUNNEL(GRAPHICS&);
	TUNNEL(const TUNNEL&) = delete;
	TUNNEL& operator= (const TUNNEL&) = delete;
	~TUNNEL() noexcept;

	void Draw() noexcept;
};
