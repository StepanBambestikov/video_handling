#include "pch.h"
#include "test_painter_service_functions.h"
#include <random>

pixel_type random_pixel_color()
{
	std::random_device rd;
	std::mt19937 rng(rd());
	std::uniform_int_distribution<size_t> uni(0, 255);
	uchar random_1 = uni(rng);
	uchar random_2 = uni(rng);
	uchar random_3 = uni(rng);
	return pixel_type{ { random_1, random_2, random_3 } };
}

std::vector<pixel_type> get_random_colors_vector(size_t color_number) 
{
	std::vector<pixel_type> colors;
	colors.reserve(color_number);
	for (auto i = 0; i < color_number; ++i) {
		colors.push_back(random_pixel_color());
	}
	return colors;
}