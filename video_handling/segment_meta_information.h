#pragma once
#include "edge.h"

class segment_meta_information final{
public:

	segment_meta_information(size_t _segment_size, const edge& _longest_segment_edge) noexcept;

	[[nodiscard]] size_t get_segment_size() const noexcept;
	[[nodiscard]] edge get_longest_segment_edge() const noexcept;

	static const size_t BEGIN_SEGMENT_SIZE;
	static const segment_meta_information SEGMENT_WITH_ONE_ELEMENT_INFO;
private:
	size_t segment_size;
	edge longest_segment_edge;
};
