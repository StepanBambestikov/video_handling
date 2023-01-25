#pragma once
#include "OpenCV.h"
#include "Image.h"

class output_video final {
public:
	output_video(std::shared_ptr<cv::VideoWriter> _video_ptr);
	output_video(std::string video_file_name, size_t image_width, size_t image_height);

	void operator <<(const Image& image) const;
private:
	std::shared_ptr<cv::VideoWriter> video_ptr;
};
