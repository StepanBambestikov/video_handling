#include "pixel_border_highlighter.h"
#include "graph_based_frame_segmenter.h"
#include "color_distance_counter.h"

namespace {

	bool pixel_is_border(const image_segments& segments, size_t x, size_t y, Image origin_image){
		auto seg_id = segments.get_segment_id(origin_image.get_pixel_id_from_coords(x, y));

		if (x == 0 || y == 0) {
			return false;
		}
		for (auto current_x = x - 1; current_x < x + 2 && current_x < origin_image.get_width(); ++current_x) {
			for (auto current_y = y - 1; current_y < y + 2 && current_y < origin_image.get_height(); ++current_y) {
				if (seg_id != segments.get_segment_id(origin_image.get_pixel_id_from_coords(current_x, current_y))) {
					return true;
				}
			}
		}
		return false;
	}
}

pixel pixel_border_highlighter::operator()(const image_segments& segments, size_t x, size_t y, Image origin_image){
	if (pixel_is_border(segments, x, y, origin_image)) {
		return pixel::WHITE_PIXEL;
	}
	return pixel::BLACK_PIXEL;
}