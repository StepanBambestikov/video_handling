#pragma once
#include "frame_handler.h"
#include "frame_segmenter.h"
#include "graph_based_parameter_segmentation.h"

template<class pixel_handler_type>
concept correct_pixel_handler_type = requires(pixel_handler_type pixel_handler, const image_segments & segments, 
	size_t x, size_t y, Image origin_image){
	{ pixel_handler(segments, x, y, origin_image) } -> std::same_as<pixel>;
};

template<correct_pixel_handler_type pixel_handler_type>
class segment_frame_handler final : public frame_handler{
public:
	segment_frame_handler(std::shared_ptr<frame_segmenter> _segmenter_ptr, std::shared_ptr<pixel_handler_type> _pixel_handler_ptr,
		graph_based_parameter_segmentation _TEST_MERGE_CONSTANT, size_t _MIN_SEGMENT_SIZE);

	[[nodiscard]] Image process_image(Image origin_image) override;
private:
	std::shared_ptr<frame_segmenter> segmenter_ptr;
	std::shared_ptr<pixel_handler_type> pixel_handler_ptr;
	graph_based_parameter_segmentation TEST_MERGE_CONSTANT = { 1000 };
	size_t MIN_SEGMENT_SIZE = { 1000 };

	bool max_element_id_was_initialized = { false };
};

template<correct_pixel_handler_type pixel_handler_type>
segment_frame_handler<pixel_handler_type>::segment_frame_handler(std::shared_ptr<frame_segmenter> _segmenter_ptr, std::shared_ptr<pixel_handler_type> _pixel_handler_ptr,
	graph_based_parameter_segmentation _TEST_MERGE_CONSTANT, size_t _MIN_SEGMENT_SIZE) : segmenter_ptr(_segmenter_ptr), pixel_handler_ptr(_pixel_handler_ptr),
TEST_MERGE_CONSTANT(_TEST_MERGE_CONSTANT), MIN_SEGMENT_SIZE(_MIN_SEGMENT_SIZE) {}

template<correct_pixel_handler_type pixel_handler_type>
Image segment_frame_handler<pixel_handler_type>::process_image(Image origin_image){
	Image output_image = origin_image;

	if (!max_element_id_was_initialized) {
		size_t _max_pixel_id = origin_image.get_pixel_count();
		element_id::initialize_max_element_id(_max_pixel_id);

		max_element_id_was_initialized = true;
	}

	auto segments = segmenter_ptr->segment_frame(origin_image, TEST_MERGE_CONSTANT, MIN_SEGMENT_SIZE);

	for (const auto& pixel_id : element_id::for_loop_element_id){
		auto x = origin_image.get_x_from_pixel_id(pixel_id);
		auto y = origin_image.get_y_from_pixel_id(pixel_id);

		output_image.set(x, y, (*pixel_handler_ptr)(segments, x, y, origin_image));
	}

	return output_image;
}