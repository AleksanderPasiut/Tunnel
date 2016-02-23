#include <cmath>

#include "tunnel.h"

#define frand static_cast<float>(dis(gen))
const float pi = 3.141592f;

void TUNNEL::CreateNewCube()
{
	if (frand > creation_properties.creation_chance)
		return;
	
	float radius = creation_properties.radius.span*frand+creation_properties.radius.min;
	float angle = frand*2*pi;

	D3DXVECTOR3 init_pos(
		-creation_properties.boundary,
		radius*cos(angle),
		radius*sin(angle));

	D3DXVECTOR3 init_scale(
		creation_properties.scale.span*frand+creation_properties.scale.min,
		creation_properties.scale.span*frand+creation_properties.scale.min,
		creation_properties.scale.span*frand+creation_properties.scale.min);

	D3DXCOLOR init_color = creation_properties.color.min*frand+creation_properties.color.span;

	CUBE* new_cube = new CUBE(
		graphics,
		init_pos,
		init_scale,
		init_color,
		creation_properties.speed.span*frand+creation_properties.speed.min,
		creation_properties.boundary);

	cube_array.push_back(new_cube);
}

TUNNEL::TUNNEL(GRAPHICS& in_graphics) : 
	graphics(in_graphics),
	rd(),
	gen(rd()),
	dis(0,1)
{
	creation_properties = 
	{
		0.5f,
		250.0f,
		{ 0.5f, 6.0f },
		{ 0.1f, 0.4f },
		{ D3DXCOLOR(0.3f, 0.3f, 0.7f, 1.0f), D3DXCOLOR(0.1f, 0.1f, 0.1f, 1.0f) },
		{ 0.8f, 0.0f },
	};	
}

TUNNEL::~TUNNEL() noexcept
{
	for (int i = 0; i < cube_array.size(); i++)
		delete cube_array[i];
}

void TUNNEL::Animate() noexcept
{
	CreateNewCube();

	if (cube_array.size())
	{
		for (auto i = cube_array.begin(); i != cube_array.end(); )
		{
			if (((*i)->animate()))
				i++;
			else
			{
				delete *i;
				i = cube_array.erase(i);
			}
		}
	}
}

void TUNNEL::Draw() noexcept
{
	for (int i = 0; i < cube_array.size(); i++)
		cube_array[i]->draw();
}