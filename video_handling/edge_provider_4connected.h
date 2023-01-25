#pragma once
#include <vector>
#include "Image.h"
#include "edge.h"
#include "edge_from_image_provider.h"

template<class distance_counter>
concept distance_counter_type = std::is_default_constructible_v<distance_counter> &&
	requires(const distance_counter& counter, const pixel & first_pixel, const pixel & second_pixel){
	{ counter(first_pixel, second_pixel) } -> std::same_as<length>;
};

using edges_set = std::vector<edge>;

template<distance_counter_type distance_counter>
class edge_provider_4connected final : public edges_from_image_provider{
public:
	edge_provider_4connected() = default;
	[[nodiscard]] edges_set get_edges_from_image(Image image) const override;

private:
	
	static edge get_vertical_edge(Image& image, distance_counter& counter,
		size_t current_height, size_t current_width){
		auto distance = counter(image.get(current_width, current_height), image.get(current_width, current_height + 1));
		auto first_id = image.get_pixel_id_from_coords(current_width, current_height);
		auto second_id = image.get_pixel_id_from_coords(current_width, current_height + 1);
		return { first_id, second_id, distance };
	}

	static edge get_horizontal_edge(Image& image, distance_counter& counter,
		size_t current_height, size_t current_width){
		auto distance = counter(image.get(current_width, current_height), image.get(current_width + 1, current_height));
		auto first_id = image.get_pixel_id_from_coords(current_width, current_height);
		auto second_id = image.get_pixel_id_from_coords(current_width + 1, current_height);
		return { first_id, second_id, distance };
	}
};

template<distance_counter_type distance_counter>
edges_set edge_provider_4connected<distance_counter>::get_edges_from_image(Image image) const{

	auto counter = distance_counter{};
	auto image_height = image.get_height();
	auto image_width = image.get_width();

	std::vector<edge> edges{};

	for (auto current_width = 0; current_width < image_width - 1; ++current_width){
		for (auto current_height = 0; current_height < image_height - 1; ++current_height){
			edges.emplace_back(get_vertical_edge(image, counter, current_height, current_width));
			edges.emplace_back(get_horizontal_edge(image, counter, current_height, current_width));
		}
		edges.emplace_back(get_horizontal_edge(image, counter, image_height - 1, current_width));
	}

	for (auto current_height = 0; current_height < image_height - 1; ++current_height){
		edges.emplace_back(get_vertical_edge(image, counter, current_height, image_width - 1));
	}

	return edges;
}