#pragma once
#include <vector>
#include "element_id.h"

class disjoint_set final{
	class disjoint_set_iterator;

public:
	using iterator = disjoint_set_iterator;

	disjoint_set();
	[[nodiscard]] element_id find_union(element_id id) noexcept;
	void merge_unions(element_id first_id, element_id second_id) noexcept;
	[[nodiscard]] element_id get_parent_id(element_id pixel_id) const noexcept;

	iterator begin() noexcept;
	iterator end() noexcept;

	friend class disjoint_set_iterator;

private:
	std::vector<element_id> parents_id;

	class disjoint_set_iterator final{
		using inner_iterator_type = std::vector<element_id>::iterator;

	public:
		disjoint_set_iterator(inner_iterator_type _inner_iterator);

		disjoint_set_iterator& operator++();
		element_id& operator*();

		bool operator==(const disjoint_set_iterator& other_iterator) const;
		bool operator!=(const disjoint_set_iterator& other_iterator) const;

	private:
		inner_iterator_type inner_iterator;
	};
};
