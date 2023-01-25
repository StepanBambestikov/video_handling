#pragma once
#include <shared_mutex>

#include "image_element.h"
#include "output_video.h"

class thread_safe_output_video final {
public:
	thread_safe_output_video(output_video video);
	void operator <<(const image_element& inserting_element) const;

private:
	output_video video;

	mutable std::list < image_element > images_container;
	mutable size_t next_element_id_for_taking = { 0 };

	mutable std::mutex video_mutex;
	mutable std::mutex container_mutex;
	mutable std::shared_mutex next_element_id_mutex;
	//mutable std::shared_mutex next_element_id_read_mutex;

	void insert_element_in_right_order(const image_element& inserting_element) const;
	void take_valid_element_from_captured_container() const;
	void add_element_to_video(const image_element& inserting_element) const;
	void take_all_valid_elements_from_container() const;
};