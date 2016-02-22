#include "graphics.h"

void GRAPHICS::CreateDirect3DDevice()
{
	DWORD quality = 0;
	d3d->CheckDeviceMultiSampleType(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		D3DFMT_X8R8G8B8,
		true,
		D3DMULTISAMPLE_8_SAMPLES,
		&quality);

	ZeroMemory(&d3dpp, sizeof(D3DPRESENT_PARAMETERS));
	d3dpp.Windowed = true;
	d3dpp.hDeviceWindow = hwnd;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
	d3dpp.BackBufferWidth = GetSystemMetrics(SM_CXSCREEN);
	d3dpp.BackBufferHeight = GetSystemMetrics(SM_CYSCREEN);
	d3dpp.MultiSampleType = D3DMULTISAMPLE_8_SAMPLES;
	d3dpp.MultiSampleQuality = quality - 1;
	d3dpp.EnableAutoDepthStencil = true;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;

	if (FAILED(d3d->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hwnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp,
		&d3ddev)))
		throw 0;

	d3ddev->SetRenderState(D3DRS_ZENABLE, true);
	d3ddev->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	d3ddev->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	d3ddev->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	d3ddev->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}
void GRAPHICS::InitColorsNMaterials() noexcept
{
	color_back = D3DCOLOR_XRGB(0, 0, 0);
}
void GRAPHICS::InitLights() noexcept
{
	d3ddev->SetRenderState(D3DRS_LIGHTING, true);
	d3ddev->SetRenderState(D3DRS_AMBIENT, D3DCOLOR_XRGB(50, 50, 50));

	D3DLIGHT9 light;
	ZeroMemory(&light, sizeof(D3DLIGHT9));
	light.Type = D3DLIGHT_DIRECTIONAL;
	light.Diffuse = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
	light.Direction = D3DXVECTOR3(-1.0f,  0.0f,  0.0f);

	d3ddev->SetLight(0, &light);
	d3ddev->LightEnable(0, true);
}

void GRAPHICS::UpdateMatrixWorld() noexcept
{
	D3DXMATRIX m1, m2;
	D3DXMatrixMultiply(
		&strWorld.matWorld,
		D3DXMatrixRotationZ(&m1, strWorld.rotationZ),
		D3DXMatrixRotationY(&m2, strWorld.rotationY));
}
void GRAPHICS::UpdateMatrixView() noexcept
{
	D3DXMatrixLookAtLH(&strView.matView,
		&strView.camera_pos,
		&strView.look_at_point,
		&strView.up_direction);
}
void GRAPHICS::UpdateMatrixProjection() noexcept
{
	RECT rect;
	GetClientRect(hwnd, &rect);

	D3DXMatrixPerspectiveFovLH(&strProjection.matProjection,
		D3DXToRadian(strProjection.angle),
		static_cast<float>(rect.right-rect.left)/static_cast<float>(rect.bottom-rect.top),
		strProjection.plane_near,
		strProjection.plane_far);
}

GRAPHICS::GRAPHICS(HWND in_hwnd) : 
	hwnd(in_hwnd)
{
	try
	{
		d3d = Direct3DCreate9(D3D_SDK_VERSION);
		if (!d3d)
			throw 0;

		try
		{
			CreateDirect3DDevice();
			InitColorsNMaterials();
			InitLights();
			
			strWorld.rotationY = 0.0f;
			strWorld.rotationZ = 0.0f;
			strView.camera_pos = D3DXVECTOR3(5.0f, 0.0f, 0.0f);
			strView.look_at_point = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			strView.up_direction = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
			strProjection.angle = 45;
			strProjection.plane_near = 1.0f;
			strProjection.plane_far = 100.0f;
			UpdateMatrixWorld();
			UpdateMatrixView();
			UpdateMatrixProjection();
		}
		catch(...) { d3d->Release(); throw; }
	}
	catch(...) { throw; }
}

GRAPHICS::~GRAPHICS() noexcept
{
	d3ddev->Release();
	d3d->Release();
}

void GRAPHICS::BeginScene() noexcept
{
	d3ddev->Clear(0, 0, D3DCLEAR_TARGET, color_back, 1.0f, 0);
	d3ddev->Clear(0, 0, D3DCLEAR_ZBUFFER, color_back, 1.0f, 0);

	d3ddev->BeginScene();

	d3ddev->SetTransform(D3DTS_VIEW, &strView.matView);
	d3ddev->SetTransform(D3DTS_PROJECTION, &strProjection.matProjection);

	d3ddev->SetFVF(CUSTOMFVF_TYPE);
}

void GRAPHICS::EndScene() noexcept
{
	d3ddev->EndScene();
	d3ddev->Present(0, 0, 0, 0);
}