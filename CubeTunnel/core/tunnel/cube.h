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
	inline void InitMaterial() noexcept;
	inline void InitPlacement() noexcept;
	inline void InitAnimation() noexcept;

public:
	CUBE(GRAPHICS&);
	CUBE(const CUBE&) = delete;
	CUBE& operator= (const CUBE&) = delete;
	~CUBE() noexcept;

	void animate() noexcept;
	void draw() noexcept;
};