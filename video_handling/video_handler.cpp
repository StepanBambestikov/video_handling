#include "video_handler.h"
#include <memory>

video_handler::video_handler(std::shared_ptr<frame_handler> _handler_ptr) : handler_ptr(_handler_ptr) {}

void video_handler::process(input_video origin_video, output_video output){
	Image current_image{};
	while (origin_video >> current_image){
		Image output_image = handler_ptr->process_image(current_image);
		output << output_image;
	}
}


