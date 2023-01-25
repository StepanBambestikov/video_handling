#include "Image.h"
#include "image_exception.h"

Image::Image(cv::Mat _value) : value(_value)
{
    if (value.rows == 0 || value.cols == 0)
    {
        throw zero_area_exception();
    }
}

//Image Image::clone() const {
//    return { value.clone() };
//}

Image::Image(std::string image_file_name) : value(cv::imread(image_file_name)) {}

void Image::save(std::string output_file_name) const {
    cv::imwrite(output_file_name, value);
}

size_t Image::get_height() const {
    return value.rows;
}
size_t Image::get_width() const {
    return value.cols;
}

bool Image::empty() const noexcept {
    return value.empty();
}

size_t Image::get_x_from_pixel_id(element_id pixel_id) const {
    return pixel_id % value.cols;
}

size_t Image::get_y_from_pixel_id(element_id pixel_id) const {
    return pixel_id / value.cols;
}

element_id Image::get_pixel_id_from_coords(size_t x, size_t y) const {
    return { (y * value.cols) + x };
}

size_t Image::get_pixel_count() const {
    return (value.rows * value.cols) - 1;
}

void Image::set(int x, int y, pixel pixel) {
    value.at<cv::Vec3b>(y, x) = pixel.get_color();
}

pixel Image::get(int x, int y) const {
    return { value.at<cv::Vec3b>(y, x) };
}

const cv::Mat& Image::operator* () const {
    return value;
}

Image::operator bool() const {
    return !empty();
}