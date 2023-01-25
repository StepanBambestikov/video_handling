#include "thread_safe_output_video.h"

thread_safe_output_video::thread_safe_output_video(output_video _video) : video(_video) {}

void thread_safe_output_video::take_valid_element_from_captured_container() const
{
	video << images_container.front().get_image();
	images_container.pop_front();
}

void thread_safe_output_video::take_all_valid_elements_from_container() const{
	std::unique_lock container_lock{ container_mutex };


	while(!images_container.empty() && images_container.front().get_image_id() == next_element_id_for_taking){
		take_valid_element_from_captured_container();
		++next_element_id_for_taking;
	}
}

void thread_safe_output_video::add_element_to_video(const image_element& inserting_element) const {

	std::unique_lock video_lock{ video_mutex };
	video << inserting_element.get_image();

	std::unique_lock next_element_id_lock{ next_element_id_mutex };
	++next_element_id_for_taking;

	take_all_valid_elements_from_container();
}

void thread_safe_output_video::insert_element_in_right_order(const image_element& inserting_element) const
{
	auto current_image_id = inserting_element.get_image_id();
	auto is_first_element_that_bigger = [current_image_id](const image_element& current_element) {
		return current_element.get_image_id() > current_image_id;
	};

	std::unique_lock container_lock{ container_mutex };
	const auto& next_iterator = std::ranges::find_if(images_container.begin(), images_container.end(), is_first_element_that_bigger);
	images_container.insert(next_iterator, inserting_element);
}

void thread_safe_output_video::operator <<(const image_element& inserting_element) const{
	auto current_image_id = inserting_element.get_image_id();

	std::shared_lock next_element_read_lock{ next_element_id_mutex };
	if (current_image_id == next_element_id_for_taking){
		next_element_read_lock.unlock();

		add_element_to_video(inserting_element);
		return;
	}

	next_element_read_lock.unlock();
	insert_element_in_right_order(inserting_element);
}