#pragma once
#include "async_images_worker.h"
#include "input_video.h"
#include "thread_safe_output_video.h"
//#include "thread_save_image_container.h"
#include "video_handler.h"

class thread_video_handler final : public video_handler{
public:
	thread_video_handler(size_t threads_number, std::shared_ptr<frame_handler> image_handler_ptr);
	void process(input_video origin_video, output_video output) override;

private:
	size_t thread_max_number;
	std::shared_ptr<frame_handler> image_handler_ptr;

	std::vector<std::shared_ptr<async_images_worker>> get_async_workers(std::shared_ptr<thread_safe_input_video> thread_safe_input_video_ptr,
		std::shared_ptr<thread_safe_output_video> thread_save_output_video_ptr);
};