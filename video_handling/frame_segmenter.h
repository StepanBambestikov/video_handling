#pragma once
#include "Image.h"
#include "edge_from_image_provider.h"
#include "image_segments.h"
#include "graph_based_parameter_segmentation.h"

class frame_segmenter {
public:
	frame_segmenter(std::shared_ptr<edges_from_image_provider> _edge_provider_ptr) : edge_provider_ptr(_edge_provider_ptr) {}
	virtual ~frame_segmenter() = default;

	[[nodiscard]] virtual image_segments segment_frame
		(Image input_image, graph_based_parameter_segmentation SEGMENT_MERGE_CONSTANT
			, size_t MIN_SEGMENT_SIZE) const = 0;

protected:
	std::shared_ptr<edges_from_image_provider> edge_provider_ptr;
};
