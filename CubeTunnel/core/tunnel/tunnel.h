#pragma once

#include <vector>
#include <random>

#include "..\\graphics\\graphics.h"
#include "cube.h"

class TUNNEL
{
protected:
	GRAPHICS& graphics;
	std::vector<CUBE*> cube_array;

	std::random_device rd;
	std::mt19937 gen;
	std::uniform_real_distribution<> dis;

	template <typename T>
	struct FRAND
	{
		T min;
		T span;
	};
	struct CREATION_PROPERTIES
	{
		float creation_chance;
		float boundary;
		FRAND<float> radius;
		FRAND<float> scale;
		FRAND<D3DXCOLOR> color;
		FRAND<float> speed;
	};
	CREATION_PROPERTIES creation_properties;
	void CreateNewCube();

public:
	TUNNEL(GRAPHICS&);
	TUNNEL(const TUNNEL&) = delete;
	TUNNEL& operator= (const TUNNEL&) = delete;
	~TUNNEL() noexcept;

	void Animate() noexcept;
	void Draw() noexcept;
};
