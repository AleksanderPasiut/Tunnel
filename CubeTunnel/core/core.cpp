#include <windowsx.h>

#include "core.h"

CORE::CORE(HWND hwnd)
{
	rotating.rotationY_limit = 1.57f;
	rotating.speed = 0.0025f;

	try
	{
		graphics = new GRAPHICS(hwnd);

		try
		{
			tunnel = new TUNNEL(*graphics);
		}
		catch(...) { delete graphics; throw; }
	}
	catch(...) { throw; }
}

CORE::~CORE() noexcept
{
	delete tunnel;
	delete graphics;
}

void CORE::Animate() noexcept
{
	tunnel->Animate();
}

void CORE::RenderScene() noexcept
{
	graphics->BeginScene();
	tunnel->Draw();
	graphics->EndScene();
}

void CORE::UpdateWindowSize() noexcept
{
	graphics->UpdateMatrixProjection();
	RenderScene();
}

void CORE::MouseButtonDown(LPARAM lParam) noexcept
{
	rotating.click.x = GET_X_LPARAM(lParam);
	rotating.click.y = GET_Y_LPARAM(lParam);
	rotating.old_rotationY = graphics->RotationY();
	rotating.old_rotationZ = graphics->RotationZ();
}

void CORE::MouseMove(WPARAM wParam, LPARAM lParam) noexcept
{
	switch(wParam)
	{
		case MK_LBUTTON:
		{
			graphics->RotationY() = rotating.old_rotationY-(GET_Y_LPARAM(lParam)-rotating.click.y)*rotating.speed;
			if (graphics->RotationY() > rotating.rotationY_limit)
				graphics->RotationY() = rotating.rotationY_limit;
			if (graphics->RotationY() < -rotating.rotationY_limit)
				graphics->RotationY() = -rotating.rotationY_limit;
			graphics->RotationZ() = rotating.old_rotationZ+(GET_X_LPARAM(lParam)-rotating.click.x)*rotating.speed;
			graphics->UpdateMatrixWorld();
			break;
		}
	}
}