#pragma once
#include <vector>
#include "element_id.h"
#include "segment_id.h"

class image_segments final{
public:

	image_segments(std::vector<segment_id> segments_id);
	segment_id get_segment_id(element_id pixel_id) const noexcept;
	
private:
	std::vector<segment_id> pixel_segments;
};