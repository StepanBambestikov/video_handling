#pragma once
#include <exception>

class output_video_exception : public std::exception {};

class no_video_writer_ptr_exception final : public output_video_exception{
    [[nodiscard]] const char* what() const noexcept override;
};
