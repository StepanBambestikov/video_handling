#include "graph_based_frame_segmenter.h"
#include <algorithm>

using service = __internal__::graph_based_service;

graph_based_frame_segmenter::graph_based_frame_segmenter(std::shared_ptr<edges_from_image_provider> _edge_provider_ptr)
	: frame_segmenter(_edge_provider_ptr) {}


image_segments graph_based_frame_segmenter::segment_frame
(Image input_image, graph_based_parameter_segmentation SEGMENT_MERGE_CONSTANT
	, size_t MIN_SEGMENT_SIZE) const{
	service segment_manager{ SEGMENT_MERGE_CONSTANT, MIN_SEGMENT_SIZE };

	auto edges = edge_provider_ptr->get_edges_from_image(input_image);
	std::sort(edges.begin(), edges.end());

	auto union_trees = segment_manager.get_disjoint_set_from_sorted_edges(edges);

	return segment_manager.get_segments_from_disjoint_set(union_trees);
}