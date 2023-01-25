#pragma once
#include "Image.h"

class frame_handler{
public:
	frame_handler() = default;
	virtual ~frame_handler() = default;

	[[nodiscard]] virtual Image process_image(Image origin_image) = 0;
};