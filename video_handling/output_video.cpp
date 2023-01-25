#include "output_video.h"

output_video::output_video(std::shared_ptr<cv::VideoWriter> _video_ptr){
	video_ptr = _video_ptr;
}

output_video::output_video(std::string video_file_name, size_t image_width, size_t image_height)
	: video_ptr(std::make_shared<cv::VideoWriter>(video_file_name, cv::VideoWriter::fourcc('M', 'J', 'P', 'G'),
	 30, cv::Size(static_cast<int>(image_width), static_cast<int>(image_height)))) {}

void output_video::operator <<(const Image& image) const {
	video_ptr->write(*image);
}
