#pragma once
#include "pch.h"
#include "../video_handling/image_segments.h"

TEST(image_segments, constructor) {
	size_t max_pixel_id = 10;
	element_id::initialize_max_element_id(max_pixel_id);
	image_segments segments{{0, 1, 2, 3, 4, 5}};
	for (auto i = 0; i < 5; ++i){
		ASSERT_TRUE(segments.get_segment_id(i) == element_id(i));
	}
}

TEST(image_segments, iterator_for) {
	size_t max_pixel_id = 10000;
	element_id::initialize_max_element_id(max_pixel_id);
	std::vector<segment_id> ids;
	for (auto i = 0; i < 10000; ++i){
		ids.push_back(i);
	}
	image_segments segments{ids};

	auto count = 0;
	for (auto pixel_parent_it = segments.begin(); pixel_parent_it != segments.end(); ++pixel_parent_it){
		ASSERT_TRUE(*pixel_parent_it == static_cast<element_id>(count));

		++count;
	}

	ASSERT_TRUE(count == 10000);
}
