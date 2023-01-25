#pragma once
#include "image_segments.h"
#include "disjoint_set.h"
#include "edge.h"
#include "graph_based_parameter_segmentation.h"
#include "segment_meta_information.h"

#include <unordered_map>

namespace __internal__{

	class graph_based_service final{
	public:
		graph_based_service(graph_based_parameter_segmentation _SEGMENT_MERGE_CONSTANT, size_t _MIN_SEGMENT_SIZE);

		disjoint_set get_disjoint_set_from_sorted_edges(const std::vector<edge>& sorted_edges);

		static image_segments get_segments_from_disjoint_set(disjoint_set union_trees);

	private:
		graph_based_parameter_segmentation SEGMENT_MERGE_CONSTANT;
		size_t MIN_SEGMENT_SIZE;

		std::unordered_map<element_id, segment_meta_information, element_id::element_id_hash_function>
			segments_info;

		bool segments_are_compatible(const segment_meta_information& first_segment_info,
			const segment_meta_information& second_segment_info, const edge& edge_between_segments) const;

		void update_segments_info_and_delete_unused_segment(element_id first_segment_id, const segment_meta_information& first_segment_info,
			const segment_meta_information& second_segment_info, const edge& current_edge, element_id second_segment_id);

		void update_segments_info(element_id first_segment_id, const segment_meta_information& first_segment_info,
			const segment_meta_information& second_segment_info, const edge& current_edge);

		segment_meta_information get_segment_info(const element_id& segment_id);

		edge get_new_segment_edge(const segment_meta_information& first_segment_info,
			const segment_meta_information& second_segment_info, const edge& current_edge) const;
	};
}