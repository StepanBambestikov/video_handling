#pragma once
#include <exception>

class element_id_exception : public std::exception {};

class out_of_range_element_id_exception final : public element_id_exception{
    [[nodiscard]] const char* what() const noexcept override;
};

class initialize_max_element_id_exception final : public element_id_exception{
    [[nodiscard]] const char* what() const noexcept override;
};

class doesnt_have_initialized_max_id_exception final : public element_id_exception{
    [[nodiscard]] const char* what() const noexcept override;
};

class invalid_element_id_iterator_exception final : public element_id_exception{
    [[nodiscard]] const char* what() const noexcept override;
};