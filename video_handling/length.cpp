#include "length.h"
#include <limits>

namespace
{
	double DOUBLE_EPSILON = 0.000001;
}

length::length(double _value) noexcept : value(_value) {}

length::operator double() const noexcept{
	return value;
}

bool length::operator ==(const length& other_distance) const noexcept{
	return fabs(value - other_distance.value) < DOUBLE_EPSILON;
}

bool length::operator !=(const length& other_distance) const noexcept{
	return !(*this == other_distance);
}

bool length::operator <(const length& other_distance) const noexcept{
	return value < other_distance.value;
}

double length::get_value() const noexcept{
	return value;
}

const length length::MAX_DISTANCE = { std::numeric_limits<double>::max() };