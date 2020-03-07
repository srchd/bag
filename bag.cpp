#include "bag.h"
#include <iostream>

//Author: Sipos Richard
//Neptun: K9P7QZ


std::ostream& operator<<(std::ostream& os, const T_comm& item) {
	os << "Number: " << item.number << " Occurrence: " << item.times;
	return os;
}
std::istream& operator>>(std::istream& is, T_comm& item) {
	is >> item.number;
	return is;
}
bool Bag::is_empty() const {
	return (_vec.size() == 0);
}
bool Bag::is_exist(int num) const { //private
	for (T_comm x : _vec) {
		if (x.number == num)
			return true;
	}
	return false;
}
int Bag::index_of_element(int num) const { //private
	/*if (!is_exist(num))
		throw NON_EXIST_NUMBER;*/
	int index = 0;
	for (unsigned int i = 0; i < _vec.size(); i++) {
		if (_vec[i].number == num)
			index = i;
	}
	return index;
}
void Bag::clear_bag() {
	_vec.clear();
}
void Bag::print_that_baggie_bag() const {
	if (is_empty())
		throw EMPTY_BAG;
	for (T_comm x : _vec) {
		std::cout << x << std::endl;
	}
}
void Bag::add_element(int num) {

	if (!is_exist(num)) {	
		T_comm item;		
		item.number = num;
		item.times = 1;
		_vec.push_back(item);
	}
	else {
		int ind = index_of_element(num);
		_vec[ind].times++;
	}
}
T_comm Bag::how_many(int num) const{
	if (!is_exist(num))
		throw NOT_AN_ELEMENT;
	T_comm result;
	result.number = num;
	int ind = index_of_element(num);
	result.times = _vec[ind].times;
	return result;
}
T_comm Bag::get_most_common() const {
	if (is_empty())
		throw EMPTY_BAG;
	T_comm result;
	result.times = _vec[0].times;
	result.number = _vec[0].number;
	for (T_comm x : _vec) {
		if (x.times > result.times) {
			result.times = x.times;
			result.number = x.number;
		}
	}
	return result;
}
T_comm Bag::remove_element(const int item) {
	if (is_empty())
		throw EMPTY_BAG;
	if (!is_exist(item))
		throw NOT_AN_ELEMENT;
	int ind = index_of_element(item);
	T_comm result = _vec[ind];
	_vec[ind] = _vec.back();
	_vec.pop_back();
	return result;
}
void Bag::add_element(const T_comm& item) {
	_vec.push_back(item);
}