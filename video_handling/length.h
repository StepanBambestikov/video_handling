#pragma once

class length final{
public:
	length(double _value) noexcept;
	operator double() const noexcept;
	[[nodiscard]] bool operator ==(const length& other_distance) const noexcept;
	[[nodiscard]] bool operator !=(const length& other_distance) const noexcept;
	[[nodiscard]] bool operator <(const length& other_distance) const noexcept;
	[[nodiscard]] double get_value() const noexcept;

	static const length MAX_DISTANCE;
private:
	double value;
};