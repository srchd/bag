#pragma once
#ifndef BAG_H
#define BAG_H

#include <vector>
#include <iostream>

struct T_comm
{
	int number;
	int times;
	T_comm() : number(0), times(0) {}
	T_comm(int number) : number(number), times(0) {}
	T_comm(int number, int times) : number(number), times(times) {}

	friend std::ostream& operator<<(std::ostream& os, const T_comm& item);
	friend std::istream& operator>>(std::istream& is, T_comm& item);
};

class Bag {
private:
	std::vector<T_comm> _vec;
	bool is_exist(int num) const;
	int index_of_element(int num) const;
public:
	enum error{EMPTY_BAG, NON_EXIST_NUMBER};
	void add_element(const T_comm& item);
	void remove_element(const T_comm& item);
	int how_many(int num) const;
	int get_most_common() const;
};

#endif // !BAG_H