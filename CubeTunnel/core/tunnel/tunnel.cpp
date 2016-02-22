#include "tunnel.h"

TUNNEL::TUNNEL(GRAPHICS& in_graphics) : 
	graphics(in_graphics)
{
	cube_array.resize(1);
	cube_array[0] = new CUBE(graphics);
}

TUNNEL::~TUNNEL() noexcept
{
	for (int i = 0; i < cube_array.size(); i++)
		delete cube_array[i];
}

void TUNNEL::Animate() noexcept
{
	for(int i = 0; i < cube_array.size(); i++)
		cube_array[i]->animate();
}

void TUNNEL::Draw() noexcept
{
	for (int i = 0; i < cube_array.size(); i++)
		cube_array[i]->draw();
}