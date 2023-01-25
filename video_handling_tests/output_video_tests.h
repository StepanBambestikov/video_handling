#pragma once
#include "pch.h"
#include "../video_handling/output_video.h"

TEST(output_video, constructor) {
	auto video_ptr = std::make_shared<cv::VideoWriter>();
	auto output = output_video(video_ptr);
	cv::Mat frame;
}