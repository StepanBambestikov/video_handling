#pragma once
#include "pch.h"
#include "../video_handling/Image.h"
#include "../video_handling/color_distance_counter.h"
#include "../video_handling/edge_provider_4connected.h"
#include "../video_handling/graph_based_frame_segmenter.h"

#include <random>

using picker_type = edge_provider_4connected<color_distance_counter>;

TEST(graph_based_frame_segmenter, color_image) {
	graph_based_parameter_segmentation TEST_MERGE_CONSTANT = {1000};
	size_t MIN_SEGMENT_SIZE = { 1000 };

	auto mat = cv::imread("C:/sample.jpg");//make zero mat
	Image image = { std::make_shared<cv::Mat>(mat.clone()) };
	Image image2 = { std::make_shared<cv::Mat>(mat.clone()) };
	size_t _max_pixel_id = image.get_height() * image.get_width() + image.get_height() - 2;
	element_id::initialize_max_element_id(_max_pixel_id);

	auto provider_ptr = std::make_shared<picker_type>();
	graph_based_frame_segmenter segmenter{ provider_ptr };

	ASSERT_NO_THROW(auto segments = segmenter.segment_frame( image, TEST_MERGE_CONSTANT, MIN_SEGMENT_SIZE));

}