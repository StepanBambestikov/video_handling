#include "image_element.h"

image_element::image_element(Image _image, size_t _image_id) : image(_image), image_id(_image_id) {}

Image image_element::get_image() const noexcept{
	return image;
}

[[nodiscard]] size_t image_element::get_image_id() const noexcept{
	return image_id;
}

//[[nodiscard]] image_element::operator bool() const noexcept{
//	return image.is_valid();
//}