#include "bag.h"
#include <iostream>

std::ostream& operator<<(std::ostream& os, const T_comm& item) {
	os << "Number: " << item.number << " Incidence: " << item.times;
	return os;
}
std::istream& operator>>(std::istream& is, T_comm& item) {
	is >> item.number;
	return is;
}
bool Bag::is_empty() const { //private
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
int Bag::how_many(int num) const{
	if (!is_exist(num))
		throw NON_EXIST_NUMBER;
	int ind = index_of_element(num);
	return _vec[ind].times;
}
int Bag::get_most_common() const {
	if (is_empty())
		throw EMPTY_BAG;
	int max = _vec[0].times;
	int max_num = _vec[0].number;
	for (T_comm x : _vec) {
		if (x.times > max) {
			max = x.times;
			max_num = x.number;
		}
	}
	return max_num;
}