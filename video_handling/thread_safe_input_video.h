#pragma once
#include "image_element.h"
#include "input_video.h"

class thread_safe_input_video final{
public:
	thread_safe_input_video(input_video _video);
	//thread_safe_input_video(const input_video& video);
	bool operator >>(image_element& current_element) const;

private:
	input_video video;

	mutable size_t frame_number = { 0 };
	mutable std::mutex video_mutex;
	mutable std::mutex frame_number_mutex;
};