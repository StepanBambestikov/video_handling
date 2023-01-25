#pragma once
#include <exception>

class thread_video_handler_exception : public std::exception {};

class zero_thread_count_exception final : public thread_video_handler_exception
{
    [[nodiscard]] const char* what() const noexcept override;
};
