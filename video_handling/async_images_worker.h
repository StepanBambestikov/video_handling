#pragma once
#include <future>
#include "frame_handler.h"
#include "thread_safe_input_video.h"
#include "image_element.h"
#include "thread_safe_output_video.h"

class async_images_worker final{
public:
	async_images_worker(std::shared_ptr<frame_handler> _image_handler_ptr, std::shared_ptr<thread_safe_input_video> _input_video_ptr, std::shared_ptr<thread_safe_output_video> _output_video_ptr);
	~async_images_worker();
	void start_processing();
private:

	std::shared_ptr<frame_handler> image_handler_ptr;
	std::shared_ptr<thread_safe_input_video> input_video_ptr;
	std::shared_ptr<thread_safe_output_video> output_video_ptr;
	std::future<void> future;

	void image_process(const image_element& current_element);
};
