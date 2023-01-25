#include "pixel.h"

pixel pixel::WHITE_PIXEL = { {255, 255, 255} };
pixel pixel::BLACK_PIXEL = { {0, 0, 0} };

pixel::pixel(cv::Vec3b _color) noexcept : color(_color) {}

pixel::pixel() noexcept : color({ 0, 0, 0, }) {}

const cv::Vec3b& pixel::get_color() const noexcept{
	return color;
}

const uchar& pixel::get_r() const noexcept{
	return color[0];
}

const uchar& pixel::get_g() const noexcept{
	return color[1];
}

const uchar& pixel::get_b() const noexcept{
	return color[2];
}