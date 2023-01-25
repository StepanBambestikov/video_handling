#include "image_exception.h"

const char* zero_area_exception::what() const noexcept {
    return "image width or height cannot be equal to zero in Image::Image(std::shared_ptr<cv::Mat>)";
}