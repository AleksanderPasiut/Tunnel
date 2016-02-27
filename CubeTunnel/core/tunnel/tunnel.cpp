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
		creation_properties.scale.span.x*frand+creation_properties.scale.min.x,
		creation_properties.scale.span.y*frand+creation_properties.scale.min.y,
		creation_properties.scale.span.z*frand+creation_properties.scale.min.z);

	D3DXCOLOR init_color(
			creation_properties.color.span.r*frand+creation_properties.color.min.r,
			creation_properties.color.span.g*frand+creation_properties.color.min.g,
			creation_properties.color.span.b*frand+creation_properties.color.min.b, 1.0f);
		//D3DXCOLOR(0.909f, 0.0f, 0.592f, 1.0f);//

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
		0.6f,
		250.0f,
		{ 4.0f, 8.0f },
		{ D3DXVECTOR3(6.5f, 1.8f, 1.8f), D3DXVECTOR3(2.5f, 0.7f, 0.7f) },
		{ D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f), D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f) },
		{ 0.7f, 0.0f },
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