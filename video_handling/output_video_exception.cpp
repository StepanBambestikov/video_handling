#include "output_video_exception.h"

const char* no_video_writer_ptr_exception::what() const noexcept {
    return "invalid video pointer in output_video object";
}
