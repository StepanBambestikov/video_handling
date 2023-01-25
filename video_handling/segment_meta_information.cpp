#include "segment_meta_information.h"

segment_meta_information::segment_meta_information(size_t _segment_size,const edge& _longest_segment_edge) noexcept
	: segment_size(_segment_size), longest_segment_edge(_longest_segment_edge) {}

size_t segment_meta_information::get_segment_size() const noexcept{
	return segment_size;
}

edge segment_meta_information::get_longest_segment_edge() const noexcept{
	return longest_segment_edge;
}

const size_t segment_meta_information::BEGIN_SEGMENT_SIZE = 1;
const segment_meta_information segment_meta_information::SEGMENT_WITH_ONE_ELEMENT_INFO
= { BEGIN_SEGMENT_SIZE , edge::ZERO_EDGE };