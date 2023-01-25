#include "image_segments.h"

image_segments::image_segments(std::vector<segment_id> segments_id) : pixel_segments(std::move(segments_id)) {}

segment_id image_segments::get_segment_id(element_id pixel_id) const noexcept{
	return pixel_segments[static_cast<size_t>(pixel_id)];
}