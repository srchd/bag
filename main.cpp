#include <iostream>
#include "bag.h"
#include <string>
#include <fstream>

using namespace std;

#define NORMAL_MODE
#ifdef NORMAL_MODE

void load_file(const std::string& file_name, Bag& baggie);

int main()
{
    Bag baggie;
    load_file("numbers.txt", baggie);
    baggie.print_that_baggie_bag();
    return 0;
}
void load_file(const std::string& file_name, Bag& baggie) {
    ifstream in(file_name.c_str());
    if (in.fail()) {
        cout << "Couldn't open the file!\n";
        exit(1);
    }
    T_comm item;
    while (in >> item.number) {
        //cout << item.number;
        baggie.add_element(item.number);
    }
    in.close();
}
#endif