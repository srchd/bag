#include <iostream>
#include "bag.h"
#include <string>
#include <fstream>
#include <stdlib.h>

//Author: Sipos Richard
//Neptun: K9P7QZ


using namespace std;

#define NORMAL_MODE
#ifdef NORMAL_MODE

int read_int(const string out, int min, int max, bool nec); //felhasználó-barát: ha esetleg a felhasználó NEM egy számot írna be, ez a fgv. kezeli
                                                            // ezt az esetleges problémát, vagy ha esetleg túl nagy számot ír be pl. a menünél
                                                            // a 'nec' változó felelõs azért, hogy kell-e nézni minimumot, maximumot
                                                            // (ennek a menünél van nagy haszna)

class Menu {
private:
    Bag b;
    void write_to_stdout(); // write the menu
    void get(); // get an element (how_many)
    void write_bag(); //print the bag
    void add_from_file(); //add to the bag from the given file
    void add_from_console(); //add from console
    void remove(); //remove an element
    void clear(); //clear the bag
    void common(); //most common
    void is_this_empty(); //empty-e

public:
    void run();

};

int main()
{
    Menu m;
    m.run();
    cout << "Farewell!\n";
    return 0;
}

int read_int(const string out, int min, int max, bool nec) {
    string n;
    int res;
    bool succ = false;
    do {
        cout << out;
        cin >> n;
        /*cin.clear();
        getline(cin, n);*/
        try {
            res = stoi(n);
            succ = true;
            if (nec) {
                if (!(res >= min && res <= max)) {
                    succ = false;
                    cout << "The number must be between 0-8" << endl;
                }
            }
        }
        catch (...) {
            cout << "This is not a number!" << endl;
            succ = false;
        }

    } while (!succ);
    return res;
}


void Menu::run() {
    int choice = 0;
    do {
        write_to_stdout();
        //cout << endl << "$>>";
        choice = read_int("\n$>>> ", 0, 8, true);
        switch (choice) {
            case 1:
                get();
                break;
            case 2:
                write_bag();
                break;
            case 3:
                add_from_file();
                break;
            case 4:
                add_from_console();
                break;
            case 5:
                remove();
                break;
            case 6:
                clear();
                break;
            case 7:
                common();
                break;
            case 8:
                is_this_empty();
                break;
        }
    } while (choice != 0);
}

void Menu::write_to_stdout() {
    cout << "\n\n\n";
    cout << "0. Exit" << endl;
    cout << "1. Get an element" << endl;
    cout << "2. Write the entire bag to console" << endl;
    cout << "3. Add numbers to the bag from FILE" << endl;
    cout << "4. Add number(s) to the bag from CONSOLE" << endl;
    cout << "5. Remove an element from the bag" << endl;
    cout << "6. Clear the entire bag" << endl;
    cout << "7. Get the most common element" << endl;
    cout << "8. Is this bag empty?" << endl;
}
void Menu::get() {
    if (b.is_empty()) {
        cout << "The bag is empty" << endl;
        return;
    }
    int n = read_int("Give a number: ", 0, 0, false);
    /*cout << "Give a number: ";
    cin >> n;*/
    try {
        cout << "\n\n" << b.how_many(n) << endl;
    }
    catch (Bag::error ex) {
        if (ex == Bag::NOT_AN_ELEMENT)
            cout << "This number is NOT in the bag." << endl;
    }
}
void Menu::write_bag() {
    if (b.is_empty()) {
        cout << "The bag is empty." << endl;
        return;
    }
    b.print_that_baggie_bag();
}
void Menu::add_from_file() {
    string filename;
    cout << "Name of the file (with extension): ";
    cin >> filename;
    ifstream in(filename.c_str());
    if (in.fail()) {
        cout << "The file named '" << filename << "' does not exist in this folder." << endl;
        return;
    }
    int num;
    while (in >> num) {
        b.add_element(num);
    }
    in.close();
    cout << "Success!" << endl;
}
void Menu::add_from_console() {
    int num = read_int("Give a number: ", 0, 0, false);
    /*cout << "Give a number: ";
    cin >> num;*/
    b.add_element(num);
    cout << "\n\nThe number'" << num <<"' added successfully!" << endl;
}
void Menu::remove() {
    if (b.is_empty()) {
        cout << "The bag is empty" << endl;
        return;
    }
    int num;
    try {
        /*cout << "Give a number: ";
        cin >> num;*/
        num = read_int("Give a number: ", 0, 0, false);
        b.remove_element(num);
        cout << "\n\nThe number '" << num << "' is succesfully removed." << endl;
    }
    catch (Bag::error ex) {
        if (ex == Bag::NOT_AN_ELEMENT)
            cout << "The bag does not contain this element." << endl;
    }
    
}
void Menu::clear() {
    if (b.is_empty()) {
        cout << "The bag is already empty." << endl;
        return;
    }
    b.clear_bag();
    cout << "Bag cleared successfully." << endl;
}
void Menu::common() {
    if (b.is_empty()) {
        cout << "The bag is empty" << endl;
        return;
    }
    cout << b.get_most_common() << endl;
}
void Menu::is_this_empty() {
    if (b.is_empty()) {
        cout << "Yeah, this bag is empty." << endl;
    }
    else
        cout << "No, this bag is not empty." << endl;
}

/////////////////////// TESTS FROM HERE ////////////////////////////////////////
#else
#define CATCH_CONFIG_MAIN
#include "catch.hpp"
TEST_CASE("reading from file, handling", "numbers.txt") {
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
    CHECK(baggie.remove_element(7).times == 4);
    //CHECK(baggie.get_most_common().number == 4);
    CHECK(baggie.how_many(7).times == 4);
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
    CHECK(baggie.remove_element(7).times == 11);
    CHECK_THROWS(baggie.remove_element(5));
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