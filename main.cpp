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
    try {
        baggie.print_that_baggie_bag();
    }
    catch (Bag::error ex) {
        if (ex == Bag::EMPTY_BAG)
            cout << "The bag is empty!\n";
    }

    try {
        cout << "The most common element in the bag is: " << baggie.get_most_common() << endl;
    }
    catch (Bag::error ex) {
        if (ex == Bag::EMPTY_BAG)
            cout << "The bag is empty!\n";
    }

    int n;
    cout << "Write a number: ";
    cin >> n;

    try {
        cout << "The number " << n << " is in the bag " << baggie.how_many(n) << " times\n";
    }
    catch (Bag::error ex) {
        if (ex == Bag::NON_EXIST_NUMBER) {
            cout << "This number doesn't exist in the bag!\n";
        }
    }

    baggie.clear_bag();

    try {
        baggie.print_that_baggie_bag();
    }
    catch (Bag::error ex) {
        if (ex == Bag::EMPTY_BAG)
            cout << "The bag is empty!\n";
    }
 
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