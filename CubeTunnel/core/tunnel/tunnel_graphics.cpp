#include "tunnel.h"

void TUNNEL::CreateBoundingCube() noexcept
{
	graphics.RetDevice()->CreateVertexBuffer(
		48*sizeof(CUSTOMFVF),
		D3DUSAGE_WRITEONLY,
		CUSTOMFVF_TYPE,
		D3DPOOL_DEFAULT,
		&bounding_cube,
		0);

	CUSTOMFVF* v;
	bounding_cube->Lock(0, 0, reinterpret_cast<void**>(&v), 0);

	v[0] = CUSTOMFVF(1.0f,1.0f,1.0f,{1.0f, 0.0f, 0.0f});
	v[1] = CUSTOMFVF(1.0f,-1.0f,1.0f,{1.0f, 0.0f, 0.0f});
	v[2] = CUSTOMFVF(1.0f,1.0f,-1.0f,{1.0f, 0.0f, 0.0f});
	v[3] = CUSTOMFVF(1.0f,-1.0f,-1.0f,{1.0f, 0.0f, 0.0f});

	v[4] = CUSTOMFVF(1.0f,1.0f,1.0f,{-1.0f, 0.0f, 0.0f});
	v[5] = CUSTOMFVF(1.0f,1.0f,-1.0f,{-1.0f, 0.0f, 0.0f});
	v[6] = CUSTOMFVF(1.0f,-1.0f,1.0f,{-1.0f, 0.0f, 0.0f});
	v[7] = CUSTOMFVF(1.0f,-1.0f,-1.0f,{-1.0f, 0.0f, 0.0f});

	v[8]  = CUSTOMFVF(-1.0f,1.0f,1.0f,{1.0f, 0.0f, 0.0f});
	v[9]  = CUSTOMFVF(-1.0f,-1.0f,1.0f,{1.0f, 0.0f, 0.0f});
	v[10] = CUSTOMFVF(-1.0f,1.0f,-1.0f,{1.0f, 0.0f, 0.0f});
	v[11] = CUSTOMFVF(-1.0f,-1.0f,-1.0f,{1.0f, 0.0f, 0.0f});

	v[12] = CUSTOMFVF(-1.0f,1.0f,1.0f,{-1.0f, 0.0f, 0.0f});
	v[13] = CUSTOMFVF(-1.0f,1.0f,-1.0f,{-1.0f, 0.0f, 0.0f});
	v[14] = CUSTOMFVF(-1.0f,-1.0f,1.0f,{-1.0f, 0.0f, 0.0f});
	v[15] = CUSTOMFVF(-1.0f,-1.0f,-1.0f,{-1.0f, 0.0f, 0.0f});

	v[16] = CUSTOMFVF(-1.0f,1.0f,1.0f,{0.0f, 1.0f, 0.0f});
	v[17] = CUSTOMFVF(1.0f,1.0f,1.0f,{0.0f, 1.0f, 0.0f});
	v[18] = CUSTOMFVF(-1.0f,1.0f,-1.0f,{0.0f, 1.0f, 0.0f});
	v[19] = CUSTOMFVF( 1.0f,1.0f,-1.0f,{0.0f, 1.0f, 0.0f});

	v[20] = CUSTOMFVF(-1.0f,1.0f,1.0f,{0.0f, -1.0f, 0.0f});
	v[21] = CUSTOMFVF(-1.0f,1.0f,-1.0f,{0.0f, -1.0f, 0.0f});
	v[22] = CUSTOMFVF(1.0f,1.0f,1.0f,{0.0f, -1.0f, 0.0f});
	v[23] = CUSTOMFVF(1.0f,1.0f,-1.0f,{0.0f, -1.0f, 0.0f});

	v[24] = CUSTOMFVF(-1.0f,-1.0f,1.0f,{0.0f, 1.0f, 0.0f});
	v[25] = CUSTOMFVF(1.0f,-1.0f,1.0f,{0.0f, 1.0f, 0.0f});
	v[26] = CUSTOMFVF(-1.0f,-1.0f,-1.0f,{0.0f, 1.0f, 0.0f});
	v[27] = CUSTOMFVF(1.0f,-1.0f,-1.0f,{0.0f, 1.0f, 0.0f});

	v[28] = CUSTOMFVF(-1.0f,-1.0f,1.0f,{0.0f, -1.0f, 0.0f});
	v[29] = CUSTOMFVF(-1.0f,-1.0f,-1.0f,{0.0f, -1.0f, 0.0f});
	v[30] = CUSTOMFVF(1.0f,-1.0f,1.0f,{0.0f, -1.0f, 0.0f});
	v[31] = CUSTOMFVF(1.0f,-1.0f,-1.0f,{0.0f, -1.0f, 0.0f});

	v[32] = CUSTOMFVF(1.0f,1.0f,1.0f,{0.0f, 0.0f, 1.0f});
	v[33] = CUSTOMFVF(-1.0f,1.0f,1.0f,{0.0f, 0.0f, 1.0f});
	v[34] = CUSTOMFVF(1.0f,-1.0f,1.0f,{0.0f, 0.0f, 1.0f});
	v[35] = CUSTOMFVF(-1.0f,-1.0f,1.0f,{0.0f, 0.0f, 1.0f});

	v[36] = CUSTOMFVF(1.0f,1.0f,1.0f,{0.0f, 0.0f, -1.0f});
	v[37] = CUSTOMFVF(1.0f,-1.0f,1.0f,{0.0f, 0.0f, -1.0f});
	v[38] = CUSTOMFVF(-1.0f,1.0f,1.0f,{0.0f, 0.0f, -1.0f});
	v[39] = CUSTOMFVF(-1.0f,-1.0f,1.0f,{0.0f, 0.0f, -1.0f});

	v[40] = CUSTOMFVF(1.0f,1.0f,-1.0f,{0.0f, 0.0f, 1.0f});
	v[41] = CUSTOMFVF(-1.0f,1.0f,-1.0f,{0.0f, 0.0f, 1.0f});
	v[42] = CUSTOMFVF(1.0f,-1.0f,-1.0f,{0.0f, 0.0f, 1.0f});
	v[43] = CUSTOMFVF(-1.0f,-1.0f,-1.0f,{0.0f, 0.0f, 1.0f});

	v[44] = CUSTOMFVF(1.0f,1.0f,-1.0f,{0.0f, 0.0f, -1.0f});
	v[45] = CUSTOMFVF(1.0f,-1.0f,-1.0f,{0.0f, 0.0f, -1.0f});
	v[46] = CUSTOMFVF(-1.0f,1.0f,-1.0f,{0.0f, 0.0f, -1.0f});
	v[47] = CUSTOMFVF(-1.0f,-1.0f,-1.0f,{0.0f, 0.0f, -1.0f});

	bounding_cube->Unlock();
}

void TUNNEL::DrawBoundingCube() noexcept
{
	IDirect3DDevice9& dev = *graphics.RetDevice();
	
	dev.SetMaterial(graphics.MaterialBoundingCube());

	for (unsigned i = 0; i < 12; i++)
	{
		dev.SetStreamSource(0, bounding_cube, 4*i*sizeof(CUSTOMFVF), sizeof(CUSTOMFVF));
		dev.DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	}
	
}