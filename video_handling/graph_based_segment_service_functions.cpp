#include "graph_based_segment_service_functions.h"
#include "disjoint_set.h"
#include <algorithm>

using service = __internal__::graph_based_service;

service::graph_based_service(graph_based_parameter_segmentation _SEGMENT_MERGE_CONSTANT, size_t _MIN_SEGMENT_SIZE)
	: SEGMENT_MERGE_CONSTANT(_SEGMENT_MERGE_CONSTANT), MIN_SEGMENT_SIZE(_MIN_SEGMENT_SIZE) {}

image_segments service::get_segments_from_disjoint_set(disjoint_set union_trees){
	auto pixel_segments = std::vector<segment_id>{};
	for (auto pixel_parent : union_trees){
		pixel_segments.emplace_back(static_cast<segment_id>(union_trees.find_union(pixel_parent)));
	}
	return { pixel_segments };
}


bool service::segments_are_compatible(const segment_meta_information& first_segment_info,
	const segment_meta_information& second_segment_info,const edge& edge_between_segments) const{
	double first_merge_addition = SEGMENT_MERGE_CONSTANT / static_cast<double>(first_segment_info.get_segment_size());
	double second_merge_addition = SEGMENT_MERGE_CONSTANT / static_cast<double>(second_segment_info.get_segment_size());

	length measure_criterion = std::min(first_segment_info.get_longest_segment_edge().get_distance() + first_merge_addition,
		second_segment_info.get_longest_segment_edge().get_distance() + second_merge_addition);

	return edge_between_segments.get_distance() < measure_criterion;
}


disjoint_set service::get_disjoint_set_from_sorted_edges(const std::vector<edge>& sorted_edges){
	disjoint_set vertices_parents{};

	for (auto& current_edge : sorted_edges){
		auto first_segment_id = vertices_parents.find_union(current_edge.get_begin());
		auto second_segment_id = vertices_parents.find_union(current_edge.get_end());

		if (first_segment_id == second_segment_id){
			continue;
		}

		segment_meta_information first_segment_info = get_segment_info(first_segment_id);
		segment_meta_information second_segment_info = get_segment_info(second_segment_id);

		
		if (first_segment_info.get_segment_size() >= MIN_SEGMENT_SIZE && second_segment_info.get_segment_size() >= MIN_SEGMENT_SIZE 
			&& !segments_are_compatible(first_segment_info, second_segment_info, current_edge)){
			continue;
		}

		if (second_segment_info.get_segment_size() != segment_meta_information::BEGIN_SEGMENT_SIZE){
			update_segments_info_and_delete_unused_segment(first_segment_id, first_segment_info, second_segment_info, current_edge, second_segment_id);
		}
		else{
			update_segments_info(first_segment_id, first_segment_info, second_segment_info, current_edge);
		}

		vertices_parents.merge_unions(first_segment_id, second_segment_id);
	}
	return vertices_parents;
}

edge service::get_new_segment_edge(const segment_meta_information& first_segment_info,
	const segment_meta_information& second_segment_info, const edge& current_edge) const{
	if (first_segment_info.get_segment_size() < MIN_SEGMENT_SIZE && second_segment_info.get_segment_size() >= MIN_SEGMENT_SIZE){
		return second_segment_info.get_longest_segment_edge();
	}
	if (first_segment_info.get_segment_size() >= MIN_SEGMENT_SIZE && second_segment_info.get_segment_size() < MIN_SEGMENT_SIZE){
		return first_segment_info.get_longest_segment_edge();
	}
	return current_edge;
}

void service::update_segments_info(element_id first_segment_id, const segment_meta_information& first_segment_info,
	const segment_meta_information& second_segment_info, const edge& current_edge){
	auto new_segment_size = first_segment_info.get_segment_size() + second_segment_info.get_segment_size();
	auto new_segment_edge = get_new_segment_edge(first_segment_info, second_segment_info, current_edge);
	segment_meta_information new_segment_info{ new_segment_size, new_segment_edge };
	segments_info.insert_or_assign(first_segment_id, new_segment_info);
}

void service::update_segments_info_and_delete_unused_segment(element_id first_segment_id, const segment_meta_information& first_segment_info,
	const segment_meta_information& second_segment_info, const edge& current_edge, element_id second_segment_id){
	update_segments_info(first_segment_id, first_segment_info, second_segment_info, current_edge);
	segments_info.erase(second_segment_id);
}

segment_meta_information service::get_segment_info(const element_id& segment_id){
	auto segment_info_it = segments_info.find(segment_id);
	if (segment_info_it != segments_info.end()){
		return segment_info_it->second;
	}
	return segment_meta_information::SEGMENT_WITH_ONE_ELEMENT_INFO;
}