#pragma once
#include "pch.h"
#include "../video_handling/Image.h"

TEST(Image, for_loop_all_image){
	auto image_ptr = std::make_shared<cv::Mat>(260, 301, CV_8UC3, cv::Scalar(0, 0, 0));
	Image image = { image_ptr };

	for(auto x = 0; x < image.get_width(); ++x){
		for (auto y = 0; y < image.get_height(); ++y){
			auto pixel = image.get(x, y);
		}
	}
}

TEST(Image, clone){
	auto image_ptr = std::make_shared<cv::Mat>(260, 301, CV_8UC3, cv::Scalar(0, 0, 0));
	Image image = { image_ptr };
	Image copy_image = image.clone();

	copy_image.set(1, 1, { {1, 2, 3} });
	ASSERT_TRUE(copy_image.get(1, 1).get_r() == 1);
	ASSERT_TRUE(copy_image.get(1, 1).get_g() == 2);
	ASSERT_TRUE(copy_image.get(1, 1).get_b() == 3);

	ASSERT_TRUE(image.get(1, 1).get_r() != 1);
	ASSERT_TRUE(image.get(1, 1).get_g() != 2);
	ASSERT_TRUE(image.get(1, 1).get_b() != 3);
}