#pragma once
#include "pch.h"
#include "../video_handling/graph_based_segment_service_functions.h"

using test_service = __internal__::graph_based_service;

TEST(get_segments_from_union_trees, nothing_changing_transformation) {
	size_t max_pixel_id = 10000;
	element_id::initialize_max_element_id(max_pixel_id);
	auto union_trees = disjoint_set();

	auto segments = test_service::get_segments_from_disjoint_set(union_trees);

	for (auto i = 0; i < 10000; ++i){
		ASSERT_TRUE(segments.get_segment_id(i) == union_trees.get_parent_id(i));
	}
}

TEST(get_segments_from_union_trees, average_work_with_4_pixels) {
	size_t max_pixel_id = 3;
	element_id::initialize_max_element_id(max_pixel_id);
	auto union_trees = disjoint_set();

	union_trees.merge_unions({0}, {1});
	union_trees.merge_unions({3}, {1});

	ASSERT_TRUE(union_trees.get_parent_id(0) == static_cast<element_id>(3));
	ASSERT_TRUE(union_trees.get_parent_id(1) == static_cast<element_id>(0));
	ASSERT_TRUE(union_trees.get_parent_id(2) == static_cast<element_id>(2));
	ASSERT_TRUE(union_trees.get_parent_id(3) == static_cast<element_id>(3));

	auto segments = test_service::get_segments_from_disjoint_set(union_trees);

	ASSERT_TRUE(segments.get_segment_id(0) == static_cast<segment_id>(3));
	ASSERT_TRUE(segments.get_segment_id(1) == static_cast<segment_id>(3));
	ASSERT_TRUE(segments.get_segment_id(2) == static_cast<segment_id>(2));
	ASSERT_TRUE(segments.get_segment_id(3) == static_cast<segment_id>(3));
}

TEST(get_segments_from_union_trees, all_pixels_in_one_set_transformation) {
	size_t max_pixel_id = 10000;
	element_id::initialize_max_element_id(max_pixel_id);
	auto union_trees = disjoint_set();

	for(size_t i = 0; i < 10000; ++i){
		union_trees.merge_unions({ i }, { i + 1 });
	}

	auto segments = test_service::get_segments_from_disjoint_set(union_trees);

	for (auto i = 0; i <= 10000; ++i){
		ASSERT_TRUE(segments.get_segment_id(i) == union_trees.get_parent_id(0));
	}
}


TEST(get_union_trees_from_sorted_edges, average_work_check) {
	test_service service_man{100, 3};
	size_t max_pixel_id = 3;
	element_id::initialize_max_element_id(max_pixel_id);
	std::vector<edge> edges = {{0, 1, 2},
		{1, 2, 4} , {0, 2, 5},
	{3, 1, 6}};

	auto union_trees = service_man.get_disjoint_set_from_sorted_edges(edges);
	auto i = union_trees;
}