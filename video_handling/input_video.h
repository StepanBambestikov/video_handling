#pragma once
#include "OpenCV.h"
#include "Image.h"

class input_video final{
public:
	input_video(std::shared_ptr<cv::VideoCapture> _video_ptr);
	input_video(std::string video_file_name);

	bool operator >>(Image& current_image) const;
	[[nodiscard]] size_t get_width() const;
	[[nodiscard]] size_t get_height() const;
	[[nodiscard]] size_t get_frame_count() const;

protected:
	std::shared_ptr<cv::VideoCapture> video_ptr;
	mutable size_t frame_number = { 0 };
};
