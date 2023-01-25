#include "element_id_exception.h"

const char* out_of_range_element_id_exception::what() const noexcept {
    return "id cannot be bigger than MAX_LEVEL in element_id::element_id(size_t _id)";
}

const char* initialize_max_element_id_exception::what() const noexcept {
    return "method element_id::initialize_max_element_id(size_t) cannot be called, "
		   "when count of existing instances is more than zero.";
}

const char* doesnt_have_initialized_max_id_exception::what() const noexcept {
    return "element_id::element_id(size_t) cannot be used, when max_element wasnt initialized";
}

const char* invalid_element_id_iterator_exception::what() const noexcept {
    return "method operator*() cannot be used for invalid iterator";
}

