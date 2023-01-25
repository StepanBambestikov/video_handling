#pragma once
#include <memory>


class element_id final{

	class element_id_iterator;
public:
	using iterator = element_id_iterator;

	element_id(size_t _id);
	element_id(const element_id& other_id);
	~element_id();
	operator size_t() const noexcept;

	[[nodiscard]] bool operator ==(const element_id& other_id) const noexcept;
	[[nodiscard]] bool operator !=(const element_id& other_id) const noexcept;
	[[nodiscard]] size_t get_id() const noexcept;

	[[nodiscard]] static  size_t get_all_pixels_count() noexcept;

	static [[nodiscard]] iterator begin();
	static [[nodiscard]] iterator end();

	static void initialize_max_element_id(size_t _MAX_ELEMENT_ID);

	[[nodiscard]] static element_id get_max_element_id();
	[[nodiscard]] static element_id get_void_element();

	static element_id for_loop_element_id;

	class element_id_hash_function{
	public:
		size_t operator()(const element_id& elem_id) const;
	};
private:
	size_t id;

	static size_t DEFAULT_MAX_ELEMENT_ID;
	static size_t MAX_ELEMENT_ID;
	static size_t existing_number;
	static bool max_element_was_initialized;

	class element_id_iterator final{
	public:
		element_id_iterator() = default;
		element_id_iterator(std::shared_ptr<element_id> _id_ptr);

		element_id_iterator& operator++();
		element_id& operator*();

		[[nodiscard]] bool operator==(const element_id_iterator& other_iterator) const;
		[[nodiscard]] bool operator!=(const element_id_iterator& other_iterator) const;

	private:
		std::shared_ptr<element_id> id_ptr;
		bool is_valid = { false };
	};
};