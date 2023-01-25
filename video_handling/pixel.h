#pragma once
#include "OpenCV.h"

class pixel final{
public:
	pixel(cv::Vec3b _color) noexcept;
	pixel() noexcept;

	[[nodiscard]] const cv::Vec3b& get_color() const noexcept;
	[[nodiscard]] const uchar& get_r() const noexcept;
	[[nodiscard]] const uchar& get_g() const noexcept;
	[[nodiscard]] const uchar& get_b() const noexcept;

	static pixel WHITE_PIXEL;
	static pixel BLACK_PIXEL;

private:
	cv::Vec3b color;
};
