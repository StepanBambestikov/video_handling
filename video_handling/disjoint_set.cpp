#include "disjoint_set.h"

using iterator_namespace = disjoint_set::iterator;

disjoint_set::disjoint_set(){
	parents_id.reserve(element_id::get_all_pixels_count());
	for (auto current_index : element_id::for_loop_element_id){
		parents_id.emplace_back(current_index);
	}
}

element_id disjoint_set::find_union(element_id id) noexcept{
	element_id current_id = id;
	while (parents_id[current_id] != current_id)
	{
		current_id = parents_id[current_id];
	}
	parents_id[id] = current_id;
	return current_id;
}
void disjoint_set::merge_unions(element_id first_id, element_id second_id) noexcept{
	parents_id[find_union(second_id)] = find_union(first_id);
}

element_id disjoint_set::get_parent_id(element_id pixel_id) const noexcept{
	return parents_id[static_cast<size_t>(pixel_id)];
}

disjoint_set::iterator disjoint_set::begin() noexcept{
	return { parents_id.begin() };
}

disjoint_set::iterator disjoint_set::end() noexcept{
	return { parents_id.end() };
}

iterator_namespace::disjoint_set_iterator(inner_iterator_type _inner_iterator) : inner_iterator(_inner_iterator) {}

disjoint_set::iterator& iterator_namespace::operator++(){
	++inner_iterator;
	return *this;
}

element_id& iterator_namespace::operator*(){
	return *inner_iterator;
}

bool iterator_namespace::operator==(const disjoint_set_iterator& other_iterator) const{
	return inner_iterator == other_iterator.inner_iterator;
}

bool iterator_namespace::operator!=(const disjoint_set_iterator& other_iterator) const{
	return !(*this == other_iterator);
}