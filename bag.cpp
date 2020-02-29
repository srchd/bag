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