#include <vector>
#include <random>
#include <algorithm>
#include <fstream>
#include <iostream>
#include "Room.h"
#include "Room_Hallway.h"
#include "Room_Treasure.h"
#include "Room_Boss.h"
#include "Dungeon.h"
using namespace std;

bool test_Room();
bool test_Room_Subclass();
bool test_Dungeon();

int main() {
    if (test_Room()) {
        cout << "Passed all Room Class test cases" << endl;
    }
    if (test_Dungeon()) {
        cout << "Passed all Dungeon class test casses" << endl;
    }
}
bool test_Room() {
    bool passed = true;
    Room testRoom;
    if (testRoom.get_treasure() != 0 || testRoom.get_traps() != "nothing" || testRoom.get_type() != "Basic" || testRoom.get_threatLevel() != 0.0 || testRoom.get_roomNumber() != 0) {
        passed = false;
        cout << "FAILED default constructor test case" << endl;
    }
    Room testRoom2(1);
    if (testRoom.get_treasure() != 0 || testRoom.get_traps() != "nothing" || testRoom.get_type() != "Basic" || testRoom.get_threatLevel() != 0.0 || testRoom.get_roomNumber() != 1) {
        passed = false;
        cout << "FAILED 2nd constructor test case" << endl;
    }
    Room testRoom3(1,"Basic",1.5, 20, "Pit");
    if (testRoom.get_treasure() != 20 || testRoom.get_traps() != "Pit" || testRoom.get_type() != "Basic" || testRoom.get_threatLevel() != 1.5 || testRoom.get_roomNumber() != 1) {
        passed = false;
        cout << "FAILED 3rd constructor test case" << endl;
    }
    testRoom3.set_treasure(50);
    if (testRoom3.get_treasure() != 50) {
        passed = false;
        cout << "FAILED treasure test case" << endl;
    }
    testRoom3.set_traps("Mimic");
    if (testRoom3.get_traps() != "Mimic") {
        passed = false;
        cout << "FAILED traps test case" << endl;
    }
    testRoom3.set_threatLevel(3.5);
    if (testRoom3.get_threatLevel() != 3.5) {
        passed = false;
        cout << "FAILED threat Level test case" << endl;
    }
    testRoom3.set_type("Boss Room");
    if (testRoom3.get_type() != "Boss Room") {
        passed = false;
        cout << "FAILED type test case" << endl;
    }
    testRoom3.set_roomNumber(3);
    if (testRoom3.get_roomNumber() != 3) {
        passed = false;
        cout << "FAILED room number test case" << endl;
    }

    testRoom.generate_room();
    if (testRoom.get_threatLevel() != 0.0) {
        passed = false;
        cout << "FAILED generate room test case" << endl;
    }
    return passed;
}

bool test_Dungeon() {
    bool passed = true;
    Dungeon testDung;
    if (testDung.get_name() != "Dungeon" || testDung.get_size() != 0) {
        passed = false;
        cout << "FAILED default constructor test case" << endl;
    }
    Dungeon testDung2(5,"Test Land");
    if (testDung2.get_name() != "Test Land" || testDung2.get_size() != 5) {
        passed = false;
        cout << "FAILED 2nd constructor test case" << endl;
    }
    Room room;
    room.generate_room();
    testDung2.add_to_vecRooms(room);
    if (testDung2.get_size() != 6) {
        passed = false;
        cout << "FAILED add room test case" << endl;
    }
    Dungeon testDung3;
    testDung3.set_name("Test Land 2");
    testDung3.set_size(6);
    testDung3.generate_dungeon(2,2);
    if (testDung3.get_vecRooms().size() == 0) {
        passed = false;
        cout << "FAILED generate dungeon test case" << endl;
    }


    return passed;
}