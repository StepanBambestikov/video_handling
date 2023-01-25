#include "edge.h"

edge::edge(element_id _begin, element_id _end, length _distance) noexcept :
	begin(_begin), end(_end), distance(_distance) {}

const edge edge::ZERO_EDGE = { element_id::get_void_element(),  element_id::get_void_element(), length::MAX_DISTANCE };

bool edge::operator<(const edge& other_edge) const noexcept{
	return get_distance() < other_edge.get_distance();
}

element_id edge::get_begin() const noexcept{
	return begin;
}
element_id edge::get_end() const noexcept{
	return end;
}
length edge::get_distance() const noexcept{
	return distance;
}