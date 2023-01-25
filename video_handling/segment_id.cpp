#include "segment_id.h"

segment_id::segment_id(size_t _id) noexcept : id(_id) {}

segment_id::operator size_t() const{
	return id;
}
bool segment_id::operator ==(const segment_id& seg_id) const noexcept{
	return id == seg_id.id;
}

bool segment_id::operator !=(const segment_id& seg_id) const noexcept{
	return !(*this == seg_id);
}

size_t segment_id::get_id() const noexcept{
	return id;
}
