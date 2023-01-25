#pragma once
#include "Image.h"


class image_element final{
public:
	image_element() = default;
	image_element(Image _image, size_t _image_id);

	Image get_image() const noexcept;
	[[nodiscard]] size_t get_image_id() const noexcept;
	//[[nodiscard]] operator bool() const noexcept;
private:
	Image image;
	size_t image_id;
};