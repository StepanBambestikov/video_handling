#pragma once

class graph_based_parameter_segmentation final{
public:
	graph_based_parameter_segmentation(double _value);

	[[nodiscard]] operator double() const;
	[[nodiscard]] double get_value() const;
private:
	double value;
};
