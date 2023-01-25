#include "input_video.h"

input_video::input_video(std::shared_ptr<cv::VideoCapture> _video_ptr){
	video_ptr = _video_ptr;
}

input_video::input_video(std::string video_file_name) : video_ptr(std::make_shared<cv::VideoCapture>(video_file_name)) {}

bool input_video::operator >>(Image& current_image) const {
	cv::Mat frame;
	bool capture_was_successful = video_ptr->read(frame);
	if (capture_was_successful)
	{
		current_image = { frame };
	}
	return capture_was_successful;
}

size_t input_video::get_width() const {
	return static_cast<size_t>(video_ptr->get(cv::CAP_PROP_FRAME_WIDTH));
}

size_t input_video::get_height() const {
	return static_cast<size_t>(video_ptr->get(cv::CAP_PROP_FRAME_HEIGHT));
}

size_t input_video::get_frame_count() const {
	return static_cast<size_t>(video_ptr->get(cv::CAP_PROP_FRAME_COUNT));
}