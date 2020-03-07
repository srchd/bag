#pragma once
#ifndef BAG_H
#define BAG_H

//Author: Sipos Richard
//Neptun: K9P7QZ

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
	//Bag(std::vector<T_comm> _vec) : _vec(_vec) {};
	enum error{EMPTY_BAG, NOT_AN_ELEMENT};
	void add_element(const int num); //sz�nd�kosan van 2 'add_element' function, mert f�jlb�l csak egy v�ges hossz� sz�m-sorozatot
	void add_element(const T_comm& item); // olvas be, majd megsz�molja h�nyszor van bent, ut�bbi fgv. kiz�r�lag tesztel�si c�lra lett l�trehozva
	T_comm remove_element(const int item);
	void clear_bag();
	T_comm how_many(int num) const;
	T_comm get_most_common() const;
	void print_that_baggie_bag() const;
	bool is_empty() const;
};

#endif // !BAG_H