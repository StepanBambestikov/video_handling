#pragma once

class segment_id final {
public:
	segment_id(size_t _id) noexcept;
	operator size_t() const;
	[[nodiscard]] bool operator ==(const segment_id& id) const noexcept;
	[[nodiscard]] bool operator !=(const segment_id& id) const noexcept;
	[[nodiscard]] size_t get_id() const noexcept;
private:
	size_t id;
};
