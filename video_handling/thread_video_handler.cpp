#include "thread_video_handler.h"
#include <future>
#include "thread_video_handler_exception.h"
#include "thread_safe_input_video.h"

thread_video_handler::thread_video_handler(size_t _thread_number, std::shared_ptr<frame_handler> _handler_ptr)
	: video_handler(_handler_ptr){

	if (_thread_number == 0){
		throw zero_thread_count_exception();
	}

	thread_max_number = _thread_number;
}

std::vector<std::shared_ptr<async_images_worker>> thread_video_handler::get_async_workers(std::shared_ptr<thread_safe_input_video> thread_safe_input_video_ptr,
	std::shared_ptr<thread_safe_output_video> thread_save_output_video_ptr){
	std::vector<std::shared_ptr<async_images_worker>> image_workers_ptr;

	image_workers_ptr.reserve(thread_max_number);
	while (image_workers_ptr.size() < thread_max_number){
		image_workers_ptr.push_back(std::make_shared<async_images_worker>(handler_ptr, thread_safe_input_video_ptr, thread_save_output_video_ptr));
		image_workers_ptr.back()->start_processing();
	}

	return image_workers_ptr;
}

void thread_video_handler::process(input_video origin_video, output_video output){
	auto thread_safe_input_video_ptr = std::make_shared<thread_safe_input_video>(origin_video);
	auto thread_safe_output_video_ptr = std::make_shared<thread_safe_output_video>(output);

	std::vector<std::shared_ptr<async_images_worker>> async_workers_ptr = get_async_workers(thread_safe_input_video_ptr, thread_safe_output_video_ptr);
}

