#pragma once
#include "pch.h"
#include "../video_handling/pixel_painter.h"
#include "../video_handling/graph_based_frame_segmenter.h"
#include "../video_handling/edge_provider_4connected.h"
#include "../video_handling/pixel_border_highlighter.h"
#include "../video_handling/color_distance_counter.h"

using edge_provider_type = edge_provider_4connected<color_distance_counter>;

TEST(frame_handlers, painter_and_highlighter_average_work) {
	graph_based_parameter_segmentation TEST_MERGE_CONSTANT = { 100000 };
	size_t MIN_SEGMENT_SIZE = { 1000 };

	auto mat = cv::imread("C:/sample.jpg");
	Image image = { std::make_shared<cv::Mat>(mat.clone()) };

	auto edge_provider_ptr = std::make_shared<edge_provider_type>();
	auto segmenter_ptr = std::make_shared<graph_based_frame_segmenter>(edge_provider_ptr);

	auto painter_handler = segment_frame_handler<pixel_painter>(segmenter_ptr, std::make_shared<pixel_painter>(10), TEST_MERGE_CONSTANT, MIN_SEGMENT_SIZE);
	auto borders_handler = segment_frame_handler<pixel_border_highlighter>(segmenter_ptr, std::make_shared<pixel_border_highlighter>(), TEST_MERGE_CONSTANT, MIN_SEGMENT_SIZE);

	ASSERT_NO_THROW(auto output = painter_handler.process_image(image));
	ASSERT_NO_THROW(auto output = borders_handler.process_image(image));
}
