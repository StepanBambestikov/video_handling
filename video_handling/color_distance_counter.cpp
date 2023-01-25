#include "color_distance_counter.h"

length color_distance_counter::operator()(const pixel& first_pixel, const pixel& second_pixel) const noexcept{
	return length(abs(first_pixel.get_r() - second_pixel.get_r()) +
		abs(first_pixel.get_g() - second_pixel.get_g()) +
		abs(first_pixel.get_b() - second_pixel.get_b()));
}