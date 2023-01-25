#include "graph_based_parameter_segmentation.h"

graph_based_parameter_segmentation::graph_based_parameter_segmentation(double _value) : value(_value) {}

graph_based_parameter_segmentation::operator double() const{
	return value;
}

double graph_based_parameter_segmentation::get_value() const{
	return value;
}