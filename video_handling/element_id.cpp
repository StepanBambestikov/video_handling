#include "element_id.h"
#include <functional>
#include "element_id_exception.h"

using iterator_namespace = element_id::iterator;

size_t element_id::DEFAULT_MAX_ELEMENT_ID = { 0 };
element_id element_id::for_loop_element_id = { 0 };
size_t element_id::MAX_ELEMENT_ID = { DEFAULT_MAX_ELEMENT_ID };
size_t element_id::existing_number = { 0 };
bool element_id::max_element_was_initialized = { false };

element_id::element_id(size_t _id) : id(_id){
	if (id > MAX_ELEMENT_ID){
		throw out_of_range_element_id_exception();
	}
	++existing_number;
}

element_id::element_id(const element_id& other_id) : id(other_id.id){
	++existing_number;
}

element_id::~element_id(){
	--existing_number;
	if (existing_number == 0) {
		max_element_was_initialized = false;
	}
}

element_id::operator size_t() const noexcept{
	return id;
}

bool element_id::operator ==(const element_id& other_id) const noexcept{
	return id == other_id.id;
}

bool element_id::operator !=(const element_id& other_id) const noexcept{
	return !(*this == other_id);
}

size_t element_id::get_id() const noexcept{
	return id;
}

size_t element_id::get_all_pixels_count() noexcept{
	return MAX_ELEMENT_ID + 1;
}

using iterator = element_id::iterator;

iterator element_id::begin(){
	return { std::make_shared<element_id>(0) };
}

iterator element_id::end(){
	return {};
}

void element_id::initialize_max_element_id(size_t _MAX_ELEMENT_ID){
	if (max_element_was_initialized && existing_number != 0){
		throw initialize_max_element_id_exception();
	}
	MAX_ELEMENT_ID = _MAX_ELEMENT_ID;
	existing_number = 0;
	max_element_was_initialized = true;
}

element_id element_id::get_max_element_id(){
	return { MAX_ELEMENT_ID };
}

element_id element_id::get_void_element(){
	return { 0 };
}

iterator_namespace::element_id_iterator(std::shared_ptr<element_id> _id_ptr) : id_ptr(_id_ptr), is_valid(true) {}

element_id::iterator& iterator_namespace::operator++(){
	if (*id_ptr == static_cast<element_id>(MAX_ELEMENT_ID)){
		is_valid = false;
		return *this;
	}
	++id_ptr->id;
	return *this;
}

element_id& iterator_namespace::operator*(){
	if (!is_valid){
		throw invalid_element_id_iterator_exception();
	}
	return *id_ptr;
}

bool iterator_namespace::operator==(const element_id_iterator& other_iterator) const{
	if (!is_valid && !other_iterator.is_valid){
		return true;
	}
	if (is_valid && other_iterator.is_valid){
		return *id_ptr == *other_iterator.id_ptr;
	}
	return false;
}

bool iterator_namespace::operator!=(const element_id_iterator& other_iterator) const{
	return !(*this == other_iterator);
}


size_t element_id::element_id_hash_function::operator()(const element_id& elem_id) const{
	return std::hash<size_t>()(elem_id.get_id());
}