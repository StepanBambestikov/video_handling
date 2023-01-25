#pragma once
#include "pch.h"
#include "../video_handling/disjoint_set.h"

TEST(union_find, constructor) {
	size_t max_pixel_id = 10;
	element_id::initialize_max_element_id(max_pixel_id);
	disjoint_set quantity{};
	for(auto i = 0; i < 10; ++i){
		ASSERT_TRUE(quantity.find_union(i) == element_id(i));
	}
}

TEST(union_find, merge_two_elements) {
	size_t max_pixel_id = 2;
	element_id::initialize_max_element_id(max_pixel_id);
	disjoint_set quantity{};

	for (auto i = 0; i < 2; ++i){
		ASSERT_TRUE(quantity.find_union(i) == element_id(i));
	}

	quantity.merge_unions(0, 1);
	ASSERT_TRUE(quantity.find_union(0) == element_id(0));
	ASSERT_TRUE(quantity.find_union(1) == element_id(0));
}

TEST(union_find, merge_three_elements) {
	size_t max_pixel_id = 3;
	element_id::initialize_max_element_id(max_pixel_id);
	disjoint_set quantity{};

	quantity.merge_unions(1, 0);
	quantity.merge_unions(1, 2);
	ASSERT_TRUE(quantity.find_union(0) == element_id(1));
	ASSERT_TRUE(quantity.find_union(1) == element_id(1));
	ASSERT_TRUE(quantity.find_union(2) == element_id(1));
}

TEST(union_find, merge_many_elements) {
	size_t max_pixel_id = 10000;
	element_id::initialize_max_element_id(max_pixel_id);
	disjoint_set quantity{};

	for (auto i = 0; i < max_pixel_id; ++i){
		quantity.merge_unions(i, i + 1);
	}

	for (auto i = 0; i < max_pixel_id; ++i){
		ASSERT_TRUE(quantity.find_union(i) == element_id(0));
	}
}

TEST(union_find, iterator_for) {
	size_t max_pixel_id = 10000;
	element_id::initialize_max_element_id(max_pixel_id);
	disjoint_set quantity{};

	auto count = 0;
	for (auto pixel_parent_it = quantity.begin(); pixel_parent_it != quantity.end(); ++pixel_parent_it){
		ASSERT_TRUE(*pixel_parent_it == static_cast<element_id>(count));
		*pixel_parent_it = quantity.find_union(*pixel_parent_it);

		++count;
	}

	ASSERT_TRUE(count == 10001);
}