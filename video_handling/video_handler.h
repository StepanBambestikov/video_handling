#pragma once
#include "input_video.h"
#include "output_video.h"
#include "frame_handler.h"

class video_handler{
public:
	video_handler(std::shared_ptr<frame_handler> _handler_ptr);
	virtual ~video_handler() = default;
	virtual void process(input_video origin_video, output_video output);
protected:
	std::shared_ptr<frame_handler> handler_ptr;
};