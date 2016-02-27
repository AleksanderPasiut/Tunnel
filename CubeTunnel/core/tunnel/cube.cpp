#include "cube.h"

void CUBE::InitVertexBuffer()
{
	if (FAILED(graphics.RetDevice()->CreateVertexBuffer(
		24*sizeof(CUSTOMFVF),
		D3DUSAGE_WRITEONLY,
		CUSTOMFVF_TYPE,
		D3DPOOL_DEFAULT,
		&points,
		0)))
		throw 0;

	CUSTOMFVF* v;
	points->Lock(0,0,reinterpret_cast<void**>(&v),0);

	v[0] = {1.0f,1.0f,1.0f,{1.0f, 0.0f, 0.0f}};
	v[1] = {1.0f,-1.0f,1.0f,{1.0f, 0.0f, 0.0f}};
	v[2] = {1.0f,1.0f,-1.0f,{1.0f, 0.0f, 0.0f}};
	v[3] = {1.0f,-1.0f,-1.0f,{1.0f, 0.0f, 0.0f}};

	v[4] = {-1.0f,1.0f,1.0f,{-1.0f, 0.0f, 0.0f}};
	v[5] = {-1.0f,1.0f,-1.0f,{-1.0f, 0.0f, 0.0f}};
	v[6] = {-1.0f,-1.0f,1.0f,{-1.0f, 0.0f, 0.0f}};
	v[7] = {-1.0f,-1.0f,-1.0f,{-1.0f, 0.0f, 0.0f}};

	v[8] = {-1.0f,1.0f,1.0f,{0.0f, 1.0f, 0.0f}};
	v[9] = {1.0f,1.0f,1.0f,{0.0f, 1.0f, 0.0f}};
	v[10] = {-1.0f,1.0f,-1.0f,{0.0f, 1.0f, 0.0f}};
	v[11] = {1.0f,1.0f,-1.0f,{0.0f, 1.0f, 0.0f}};

	v[12] = {-1.0f,-1.0f,1.0f,{0.0f, -1.0f, 0.0f}};
	v[13] = {-1.0f,-1.0f,-1.0f,{0.0f, -1.0f, 0.0f}};
	v[14] = {1.0f,-1.0f,1.0f,{0.0f, -1.0f, 0.0f}};
	v[15] = {1.0f,-1.0f,-1.0f,{0.0f, -1.0f, 0.0f}};

	v[16] = {1.0f,1.0f,1.0f,{0.0f, 0.0f, 1.0f}};
	v[17] = {-1.0f,1.0f,1.0f,{0.0f, 0.0f, 1.0f}};
	v[18] = {1.0f,-1.0f,1.0f,{0.0f, 0.0f, 1.0f}};
	v[19] = {-1.0f,-1.0f,1.0f,{0.0f, 0.0f, 1.0f}};

	v[20] = {1.0f,1.0f,-1.0f,{0.0f, 0.0f, -1.0f}};
	v[21] = {1.0f,-1.0f,-1.0f,{0.0f, 0.0f, -1.0f}};
	v[22] = {-1.0f,1.0f,-1.0f,{0.0f, 0.0f, -1.0f}};
	v[23] = {-1.0f,-1.0f,-1.0f,{0.0f, 0.0f, -1.0f}};

	points->Unlock();
}
void CUBE::InitMaterial(const D3DCOLORVALUE& color) noexcept
{
	ZeroMemory(&material, sizeof(D3DMATERIAL9));
	material.Ambient = color;
	material.Diffuse = color;
	material.Specular = color;
}
void CUBE::InitPlacement() noexcept
{
	D3DXMatrixMultiply(
		&placement.mat,
		D3DXMatrixScaling(
			&placement.mat_scale,
			placement.scale.x,
			placement.scale.y,
			placement.scale.z),
		D3DXMatrixTranslation(
			&placement.mat_translation,
			placement.pos.x,
			placement.pos.y,
			placement.pos.z));

}

CUBE::CUBE(GRAPHICS& in_graphics, 
	const D3DXVECTOR3& init_pos,
	const D3DXVECTOR3& init_scale,
	const D3DCOLORVALUE& color,
	float in_speed,
	float in_pos_limit) : 
	graphics(in_graphics)
{
	InitVertexBuffer();
	InitMaterial(color);

	placement.scale = init_scale;
	placement.pos = init_pos;
	placement.pos_limit = in_pos_limit;
	InitPlacement();

	animation.speed = in_speed;
}

CUBE::~CUBE() noexcept
{
	points->Release();
}

bool CUBE::animate() noexcept
{
	placement.pos.x += animation.speed;

	if (placement.pos.x > placement.pos_limit)
		return false;

	D3DXMatrixMultiply(
		&placement.mat,
		&placement.mat_scale,
		D3DXMatrixTranslation(
			&placement.mat_translation,
			placement.pos.x,
			placement.pos.y,
			placement.pos.z));

	return true;
}

void CUBE::draw() noexcept
{
	IDirect3DDevice9& dev = *graphics.RetDevice();

	dev.SetMaterial(&material);

	D3DXMATRIX tmp;
	D3DXMatrixMultiply(&tmp, &placement.mat, graphics.RetWorldMatrix());
	dev.SetTransform(D3DTS_WORLD, &tmp);

	for (unsigned i = 0; i < 6; i++)
	{
		dev.SetStreamSource(
			0,
			points,
			4*i*sizeof(CUSTOMFVF),
			sizeof(CUSTOMFVF));
		dev.DrawPrimitive(
			D3DPT_TRIANGLESTRIP,
			0,
			2);
	}
}