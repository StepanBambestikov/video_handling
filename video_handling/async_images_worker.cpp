#include "async_images_worker.h"

async_images_worker::async_images_worker(std::shared_ptr<frame_handler> _image_handler_ptr, std::shared_ptr<thread_safe_input_video> _input_video_ptr, std::shared_ptr<thread_safe_output_video> _output_video_ptr) : image_handler_ptr(_image_handler_ptr), input_video_ptr(_input_video_ptr), output_video_ptr(_output_video_ptr) {}

async_images_worker::~async_images_worker(){
	future.wait();
}

void async_images_worker::start_processing(){
	future = std::async(std::launch::async, [this]{
		image_element current_element{};
		while ((*input_video_ptr) >> current_element) {
			image_process(current_element);
		}
	});
}

void async_images_worker::image_process(const image_element& current_element){
	Image output_image = image_handler_ptr->process_image(current_element.get_image());

	image_element output_element = { output_image, current_element.get_image_id() };
	(*output_video_ptr) << output_element;
}