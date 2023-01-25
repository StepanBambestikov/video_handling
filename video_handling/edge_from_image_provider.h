#pragma once
#include <vector>
#include "Image.h"
#include "edge.h"

class edges_from_image_provider{
public:
	edges_from_image_provider() = default;
	virtual ~edges_from_image_provider() = default;

	[[nodiscard]] virtual std::vector<edge> get_edges_from_image(Image image) const = 0;
};