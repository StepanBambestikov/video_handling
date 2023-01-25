#pragma once
#include "pch.h"
#include "../video_handling/element_id_exception.h"
#include "../video_handling/segment_meta_information.h"
#include "../video_handling/color_distance_counter.h"
#include "../video_handling/element_id.h"
#include "../video_handling/length.h"
#include "../video_handling/edge.h"
#include "../video_handling/segment_id.h"

TEST(element_id, constructor) {
	{
		size_t max_pixel_id = 10;
		element_id::initialize_max_element_id(max_pixel_id);
		element_id element(10);
		ASSERT_TRUE(element.get_id() == 10);
		EXPECT_THROW(element_id::initialize_max_element_id(2), initialize_max_element_id_exception);
	}
	EXPECT_NO_THROW(element_id::initialize_max_element_id(2));
}

TEST(element_id, out_of_range) {
	size_t max_pixel_id = 10;
	element_id::initialize_max_element_id(max_pixel_id);
	EXPECT_THROW(element_id element(11), out_of_range_element_id_exception);
}

TEST(element_id, get_max_element_id) {
	size_t max_pixel_id = 10;
	element_id::initialize_max_element_id(max_pixel_id);
	ASSERT_TRUE(element_id::get_max_element_id() == static_cast<element_id>(10));
}

TEST(element_id, get_all_pixel_count) {
	size_t max_pixel_id = 10;
	element_id::initialize_max_element_id(max_pixel_id);
	ASSERT_TRUE(element_id::get_all_pixels_count() == 11);
}

TEST(element_id, element_id_hash_function) {
	size_t max_pixel_id = 10;
	element_id::initialize_max_element_id(max_pixel_id);
	const element_id element(10);
	EXPECT_NO_THROW(size_t hash_value = element_id::element_id_hash_function()(element));
}

TEST(element_id, EQ_and_not_EQ) {
	size_t max_pixel_id = 10;
	element_id::initialize_max_element_id(max_pixel_id);
	const element_id first_element(10);
	const element_id second_element(10);
	auto copy_element = first_element;
	ASSERT_TRUE(first_element == second_element);
	ASSERT_TRUE(second_element == copy_element);
	ASSERT_TRUE(copy_element == first_element);
	copy_element = { 9 };
	ASSERT_TRUE(copy_element != first_element);
}

TEST(distance_type, constructor) {
	length dist{2};
	ASSERT_TRUE(dist.get_value() == 2.0);
}

TEST(distance_type, compare_operands) {
	const length first_distance{ 2.0 };
	const length second_distance{ 2.0 };
	auto copy_distance = second_distance;
	ASSERT_TRUE(first_distance == second_distance);
	ASSERT_TRUE(second_distance == copy_distance);
	ASSERT_TRUE(copy_distance == first_distance);
	copy_distance = { 1 };
	ASSERT_TRUE(copy_distance != first_distance);
	ASSERT_TRUE(copy_distance < first_distance);
	ASSERT_TRUE(copy_distance < length::MAX_DISTANCE);
}



TEST(edge_type, constructor) {
	size_t max_pixel_id = 10;
	element_id::initialize_max_element_id(max_pixel_id);

	edge edge(1, 2, 10);
	ASSERT_TRUE(edge.get_begin() == static_cast<element_id>(1));
	ASSERT_TRUE(edge.get_end() == static_cast<element_id>(2));
	ASSERT_TRUE(edge.get_distance() == static_cast<length>(10));
}


TEST(edge_type, ZERO_EDGE_value_check) {
	size_t max_pixel_id = 2;
	element_id::initialize_max_element_id(max_pixel_id);
	using element_id = element_id;
	auto zero_edge = edge::ZERO_EDGE;
	ASSERT_TRUE(zero_edge.get_begin() == static_cast<element_id>(0));
	ASSERT_TRUE(zero_edge.get_end() == static_cast<element_id>(0));
}

TEST(edge_type, compare_operands) {
	size_t max_pixel_id = 3;
	element_id::initialize_max_element_id(max_pixel_id);

	const element_id first_id = { 2 };
	element_id second_id = { 2 };
	ASSERT_FALSE(first_id < second_id);
	second_id = { 3 };
	ASSERT_TRUE(first_id < second_id);

}

TEST(segment_id, constructor) {
	segment_id segment(12);
	ASSERT_TRUE(segment.get_id() == 12);
}

TEST(segment_id, EQ_NO_EQ_check) {
	size_t max_pixel_id = 20;
	element_id::initialize_max_element_id(max_pixel_id);
	const segment_id first_segment(12);
	const segment_id second_segment(12);
	const auto copy_segment = second_segment;
	ASSERT_TRUE(first_segment == second_segment);
	ASSERT_TRUE(second_segment == copy_segment);
	ASSERT_TRUE(copy_segment == first_segment);
}

TEST(color_distance_counter, call_operator) {
	const auto first_pixel = pixel{{ 1, 4, 2 }};
	const auto second_pixel = pixel{ { 34, 2, 1 } };
	const auto counter = color_distance_counter{};
	EXPECT_NO_THROW(length counter_result = counter(first_pixel, second_pixel););
}

TEST(segment_meta_information, all_methods) {
	size_t max_pixel_id = 100;
	element_id::initialize_max_element_id(max_pixel_id);
	const edge test_edge{ { 1 }, { 2 }, { 3.0 } };
	const segment_meta_information test_info{ 50, test_edge };

	ASSERT_TRUE(test_info.get_longest_segment_edge().get_distance() == test_edge.get_distance());
	ASSERT_TRUE(test_info.get_segment_size() == 50);
}

TEST(segment_meta_information, constructor) {
	size_t max_pixel_id = 2;
	element_id::initialize_max_element_id(max_pixel_id);
	auto segment_info = segment_meta_information(5, edge(0, 1, { 10 }));
	ASSERT_TRUE(segment_info.get_longest_segment_edge().get_distance() == static_cast<length>(10));
	ASSERT_TRUE(segment_info.get_longest_segment_edge().get_begin() == static_cast<length>(0));
	ASSERT_TRUE(segment_info.get_longest_segment_edge().get_end() == static_cast<length>(1));
	ASSERT_TRUE(segment_info.get_segment_size() == 5);
}

TEST(segment_meta_information, SEGMENT_WITH_ONE_ELEMENT_check) {
	size_t max_pixel_id = 10;
	element_id::initialize_max_element_id(max_pixel_id);

	auto segment_info = segment_meta_information::SEGMENT_WITH_ONE_ELEMENT_INFO;
	ASSERT_TRUE(segment_info.get_segment_size() == 1);
}









