#pragma once

#include "..\\graphics\graphics.h"

class CUBE
{
protected:
	GRAPHICS& graphics;
	IDirect3DVertexBuffer9* points;
	D3DMATERIAL9 material;

	struct PLACEMENT
	{
		D3DXVECTOR3 scale;
		D3DXVECTOR3 pos;
		float pos_limit;

		D3DXMATRIX mat_scale;
		D3DXMATRIX mat_translation;
		D3DXMATRIX mat;
	};
	PLACEMENT placement;

	struct ANIMATION
	{
		float speed;
	};
	ANIMATION animation;

	inline void InitVertexBuffer();
	inline void InitMaterial(const D3DCOLORVALUE&) noexcept;
	inline void InitPlacement() noexcept;

public:
	CUBE(GRAPHICS&, const D3DXVECTOR3& init_pos, const D3DXVECTOR3& init_scale, const D3DCOLORVALUE& color, float speed, float pos_limit);
	CUBE(const CUBE&) = delete;
	CUBE& operator= (const CUBE&) = delete;
	~CUBE() noexcept;

	bool animate() noexcept;
	void draw() noexcept;
};