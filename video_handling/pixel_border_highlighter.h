#pragma once
#include "segment_frame_handler.h"
#include "Image.h"

class pixel_border_highlighter final{
public:
	pixel_border_highlighter() noexcept = default;
	pixel operator()(const image_segments& segments, size_t x, size_t y, Image origin_image);
};