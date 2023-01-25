#pragma once
#include "element_id.h"
#include "pixel.h"

class Image final {
public:
    Image() = default;
    Image(cv::Mat _value);
    Image(std::string image_file_name);
    bool empty() const noexcept;

    void save(std::string output_file_name) const;
    size_t get_height() const;
    size_t get_width() const;

    [[nodiscard]] size_t get_x_from_pixel_id(element_id pixel_id) const;
    [[nodiscard]] size_t get_y_from_pixel_id(element_id pixel_id) const;

    [[nodiscard]] element_id get_pixel_id_from_coords(size_t x, size_t y) const;
    [[nodiscard]] size_t get_pixel_count() const;

    void set(int x, int y, pixel pixel);
    [[nodiscard]] pixel get(int x, int y) const;

    [[nodiscard]] const cv::Mat& operator*() const;
    [[nodiscard]] operator bool() const;
private:
    cv::Mat value;
};