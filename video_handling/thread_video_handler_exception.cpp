#include "thread_video_handler_exception.h"

const char* zero_thread_count_exception::what() const noexcept {
    return "thread count in thread_video_handler::thread_video_handler(size_t, std::shared_ptr<frame_handler>) cannot be zero ";
}