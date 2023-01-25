#pragma once
#include "pch.h"
#include "../video_handling/input_video.h"

TEST(input_video, constructor) {
	auto video_ptr = std::make_shared<cv::VideoCapture>();
	ASSERT_NO_THROW(auto input = input_video(video_ptr););
}
