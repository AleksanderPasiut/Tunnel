#pragma once

#include <vector>

#include "..\\graphics\\graphics.h"
#include "cube.h"

class TUNNEL
{
protected:
	GRAPHICS& graphics;

	std::vector<CUBE*> cube_array;

public:
	TUNNEL(GRAPHICS&);
	TUNNEL(const TUNNEL&) = delete;
	TUNNEL& operator= (const TUNNEL&) = delete;
	~TUNNEL() noexcept;

	void Animate() noexcept;
	void Draw() noexcept;
};
