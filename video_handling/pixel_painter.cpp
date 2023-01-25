#include "pixel_painter.h"
#include "graph_based_frame_segmenter.h"
#include "color_distance_counter.h"
#include "edge_provider_4connected.h"
#include <random>

namespace
{
	pixel get_random_pixel_color(){
		std::random_device rd;
		std::mt19937 rng(rd());
		std::uniform_int_distribution<size_t> uni(0, 255);
		uchar random_1 = uni(rng);
		uchar random_2 = uni(rng);
		uchar random_3 = uni(rng);
		return pixel{ { random_1, random_2, random_3 } };
	}

	std::vector<pixel> get_random_colors_vector(size_t color_number){
		std::vector<pixel> colors;
		colors.reserve(color_number);
		for (auto i = 0; i < color_number; ++i) {
			colors.push_back(get_random_pixel_color());
		}
		return colors;
	}
}

pixel_painter::pixel_painter(size_t random_colors_number) : colors(get_random_colors_vector(random_colors_number)) {}

pixel pixel_painter::get_next_color() const{
	auto& pixel = colors[current_color_number];
	if (current_color_number == colors.size() - 1) {
		current_color_number = 0;
	}
	else {
		++current_color_number;
	}

	return pixel;
}

pixel pixel_painter::operator()(const image_segments& segments, size_t x, size_t y, Image origin_image) const{
	auto seg_id = segments.get_segment_id(origin_image.get_pixel_id_from_coords(x, y));
	if (!colors_map.contains(seg_id)){
		colors_map.insert({ seg_id, get_next_color() });
	}
	return colors_map[seg_id];
}


