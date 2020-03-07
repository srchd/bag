#include <iostream>
#include "bag.h"
#include <string>
#include <fstream>

//Author: Sipos Richard
//Neptun: K9P7QZ


using namespace std;

//#define NORMAL_MODE
#ifdef NORMAL_MODE

int main()
{

    return 0;
}

#else
#define CATCH_CONFIG_MAIN
#include "catch.hpp"
TEST_CASE("reading from file", "numbers.txt") {
    const string filename = "numbers.txt";
    ifstream in(filename.c_str());
    if (in.fail()) {
        cout << "File name error!\n";
        exit(1);
    }
    Bag baggie;
    CHECK(baggie.is_empty() == true);
    int num;
    while (in >> num) {
        baggie.add_element(num);
    }
    in.close();
    CHECK(baggie.is_empty() == false);
    //end of reading, running tests below:
    CHECK(baggie.get_most_common().number == 7);
    CHECK(baggie.remove_element(7).times == 5);
    CHECK(baggie.get_most_common().number == 4);
    CHECK(baggie.how_many(-1).times == 1);
    CHECK_THROWS(baggie.how_many(800));
    CHECK_THROWS(baggie.remove_element(800));
    baggie.clear_bag();
    CHECK(baggie.is_empty() == true);
    CHECK_THROWS(baggie.get_most_common());
    CHECK_THROWS(baggie.remove_element(800));
}

TEST_CASE("remove element") {
    Bag baggie;
    CHECK_THROWS(baggie.remove_element(2));
    T_comm item(7, 12);
    T_comm item2(6, 4);
    T_comm item3(4, 420);
    baggie.add_element(item);
    baggie.add_element(item2);
    baggie.add_element(item3);
    CHECK(baggie.remove_element(7).times == 12);
    CHECK_THROWS(baggie.remove_element(7));
}
TEST_CASE("clearing the bag") {
    Bag baggie;
    T_comm item(7, 12);
    T_comm item2(6, 4);
    T_comm item3(4, 420);
    baggie.add_element(item);
    baggie.add_element(item2);
    baggie.add_element(item3);
    CHECK(baggie.is_empty() == false);
    baggie.clear_bag();
    CHECK(baggie.is_empty() == true);
}
TEST_CASE("how many") {
    Bag baggie;
    T_comm item(7, 12);
    T_comm item2(6, 4);
    T_comm item3(4, 420);
    baggie.add_element(item);
    baggie.add_element(item2);
    baggie.add_element(item3);
    CHECK_THROWS(baggie.how_many(5));
    CHECK(baggie.how_many(6).times == 4);
}
TEST_CASE("most common") {
    Bag baggie;
    CHECK_THROWS(baggie.get_most_common());
    T_comm item(7, 12);
    T_comm item2(6, 4);
    T_comm item3(4, 420);
    baggie.add_element(item);
    baggie.add_element(item2);
    baggie.add_element(item3);
    CHECK(baggie.get_most_common().number == 4);
    CHECK(baggie.get_most_common().times == 420);
}
#endif