#pragma once
#include "graph_based_parameter_segmentation.h"
#include "frame_segmenter.h"
#include "graph_based_segment_service_functions.h"

class graph_based_frame_segmenter final : public frame_segmenter{
public:
	graph_based_frame_segmenter(std::shared_ptr<edges_from_image_provider> _edge_provider_ptr);

	[[nodiscard]] image_segments segment_frame
		(Image input_image, graph_based_parameter_segmentation SEGMENT_MERGE_CONSTANT
		,size_t MIN_SEGMENT_SIZE) const override;
};