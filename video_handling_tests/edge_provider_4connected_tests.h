#pragma once
#include "pch.h"
#include "../video_handling/Image.h"
#include "../video_handling/color_distance_counter.h"
#include "../video_handling/edge_provider_4connected.h"

constexpr size_t max_pixel_id = 10;
using edge_provider_type = edge_provider_4connected<color_distance_counter>;

TEST(edge_provider_4connected, constructor) {
	EXPECT_NO_THROW(edge_provider_type provider{});
}

TEST(edge_provider_4connected, get_edges_from_image_2_2_image) {
	size_t max_pixel_id = 3;
	element_id::initialize_max_element_id(max_pixel_id);
	edge_provider_4connected<color_distance_counter> picker{};

	auto s_image_ptr = std::make_shared<cv::Mat>(2, 2, CV_8UC3, cv::Scalar(0, 0, 0));
	auto edges = picker.get_edges_from_image({ s_image_ptr });
	ASSERT_TRUE(edges.size() == 4);
}

TEST(edge_provider_4connected, get_edges_from_image_check_3_3_image) {
	size_t max_pixel_id = 8;
	element_id::initialize_max_element_id(max_pixel_id);
	edge_provider_4connected<color_distance_counter> picker{};

	auto first_image_ptr = std::make_shared<cv::Mat>(3, 3, CV_8UC3, cv::Scalar(0, 0, 0));
	auto edges = picker.get_edges_from_image({ first_image_ptr });
	ASSERT_TRUE(edges.size() == 12);

}

TEST(edge_provider_4connected, get_edges_from_image_check_100_100_image) {
	size_t max_pixel_id = 9999;
	element_id::initialize_max_element_id(max_pixel_id);
	edge_provider_4connected<color_distance_counter> picker{};

	auto second_image_ptr = std::make_shared<cv::Mat>(100, 100, CV_8UC3, cv::Scalar(0, 0, 0));
	std::vector<edge> edges_100 = picker.get_edges_from_image({ second_image_ptr });
	ASSERT_TRUE(edges_100.size() == 19800);
}

TEST(edge_provider_4connected, get_edges_from_image_check_4_3_image) {
	size_t max_pixel_id = 11;
	element_id::initialize_max_element_id(max_pixel_id);
	edge_provider_4connected<color_distance_counter> picker{};

	auto image_ptr = std::make_shared<cv::Mat>(4, 3, CV_8UC3, cv::Scalar(0, 0, 0));
	std::vector<edge> edges = picker.get_edges_from_image({ image_ptr });
	ASSERT_TRUE(edges.size() == 17);
}