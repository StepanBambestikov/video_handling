#pragma once
#include "length.h"
#include "pixel.h"

class color_distance_counter final{
public:
	color_distance_counter() = default;
	[[nodiscard]] length operator()(const pixel& first_pixel, const pixel& second_pixel) const noexcept;
};

