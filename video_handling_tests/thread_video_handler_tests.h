#pragma once
#include "pch.h"
#include "../video_handling/color_distance_counter.h"
#include "../video_handling/edge_provider_4connected.h"
#include "../video_handling/pixel_border_highlighter.h"
#include "../video_handling/thread_video_handler.h"
#include "../video_handling/graph_based_frame_segmenter.h"
#include "../video_handling/input_video.h"
#include "../video_handling/output_video.h"

TEST(thread_video_handler, average_work_with_frame_hightlighter){
	graph_based_parameter_segmentation TEST_MERGE_CONSTANT = { 10000 };
	size_t MIN_SEGMENT_SIZE = { 1000 };

	auto input_video_ptr = std::make_shared<cv::VideoCapture>("C:/input.mp4");
	input_video input = { input_video_ptr };

	auto output_ptr = std::make_shared<cv::VideoWriter>("output.avi", cv::VideoWriter::fourcc('M', 'J', 'P', 'G'), 30, cv::Size(input.get_width(), input.get_height()));
	output_video output = { output_ptr };

	auto edge_provider_ptr = std::make_shared<edge_provider_4connected<color_distance_counter>>();
	auto segmenter_ptr = std::make_shared<graph_based_frame_segmenter>(edge_provider_ptr);
	auto pixel_handler_ptr = std::make_shared<pixel_border_highlighter>();
	auto highlighter_ptr = std::make_shared<segment_frame_handler<pixel_border_highlighter>>(segmenter_ptr, pixel_handler_ptr, TEST_MERGE_CONSTANT, MIN_SEGMENT_SIZE);
	thread_video_handler handler{1,  highlighter_ptr };

	handler.process(input, output);
}