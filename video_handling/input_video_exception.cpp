#include "input_video_exception.h"

const char* no_video_capture_exception::what() const noexcept {
    return "invalid video pointer in input_video object";
}
