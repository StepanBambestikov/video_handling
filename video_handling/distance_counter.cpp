#pragma once
#include <cmath>
#include "distance_type.h"
#include "pixel_type.h"

class color_distance_counter final
{
public:
	color_distance_counter() = default;
	distance_type operator()(const pixel_type& first_pixel, const pixel_type& second_pixel) const
	{
		return abs(first_pixel.get_r() - second_pixel.get_r()) +
			abs(first_pixel.get_g() - second_pixel.get_g()) +
			abs(first_pixel.get_b() - second_pixel.get_b());
	}
};
