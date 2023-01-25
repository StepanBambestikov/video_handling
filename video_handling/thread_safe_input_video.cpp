#include "thread_safe_input_video.h"


thread_safe_input_video::thread_safe_input_video(input_video _video) : video(_video) {}

bool thread_safe_input_video::operator >>(image_element& current_element) const{
	Image image;
	std::unique_lock video_lock{ video_mutex };
	bool capture_was_successful = video >> image;
	video_lock.unlock();
	std::unique_lock frame_number_lock{frame_number_mutex};
	current_element = { image, frame_number };
	++frame_number;
	return capture_was_successful;
}