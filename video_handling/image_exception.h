#pragma once
#include <exception>

class image_exception : public std::exception {};

class zero_area_exception final : public image_exception {
    [[nodiscard]] const char* what() const noexcept override;
};