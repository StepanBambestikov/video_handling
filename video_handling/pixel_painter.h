#pragma once
#include "segment_frame_handler.h"
#include "Image.h"

class pixel_painter final{
public:
	pixel_painter(size_t random_colors_number);
	pixel operator()(const image_segments& segments, size_t x, size_t y, Image origin_image) const;
private:
	std::vector<pixel> colors;
	mutable std::unordered_map<size_t, pixel> colors_map;
	mutable size_t current_color_number = { 0 };

	pixel get_next_color() const;
};