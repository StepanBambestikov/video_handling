#pragma once
#include <exception>

class input_video_exception : public std::exception {};

class no_video_capture_exception final : public input_video_exception{
    [[nodiscard]] const char* what() const noexcept override;
};
