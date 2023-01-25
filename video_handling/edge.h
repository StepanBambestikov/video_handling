#pragma once
#include "element_id.h"
#include "length.h"

class edge final{
public:
	edge(element_id _begin, element_id _end, length _distance) noexcept;
	[[nodiscard]] element_id get_begin() const noexcept;
	[[nodiscard]] element_id get_end() const noexcept;
	[[nodiscard]] length get_distance() const noexcept;
	[[nodiscard]] bool operator<(const edge& other_edge) const noexcept;

	const static edge ZERO_EDGE;
private:
	element_id begin;
	element_id end;
	length distance;
};