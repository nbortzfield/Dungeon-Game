//
// Created by zacru on 2/21/2024.
//

#include "Room.h"

Room::Room() {
    MAXDOORS = 4;
    doors = 0;
    treasure = 0;
    traps = "nothing";
    threatLevel = 0;
    type = "Basic";
    roomNumber = 0;
    xCoordinate = 0;
    yCoordinate = 0;
}

Room::Room(int proomNumber) {
    MAXDOORS = 4;
    doors = 0;
    treasure = 0;
    traps = "nothing";
    threatLevel = 0;
    type = "Basic";
    roomNumber = proomNumber;
    xCoordinate = 0;
    yCoordinate = 0;
}

Room::Room(int proomNumber, string ptype, double pthreatlevel, int ptreasure, string ptraps, int pdoors, int pX, int pY) {
    MAXDOORS = 4;
    treasure = ptreasure;
    traps = ptraps;
    threatLevel = pthreatlevel;
    type = ptype;
    roomNumber = proomNumber;
    if (pdoors > MAXDOORS) {
        doors = MAXDOORS;
    } else {
        doors = pdoors;
    }
    xCoordinate = pX;
    yCoordinate = pY;
}

int Room::get_treasure() const {
    return treasure;
}

void Room::set_treasure(int ptreasure) {
    treasure = ptreasure;
}

double Room::get_threatLevel() const {
    return threatLevel;
}

void Room::set_threatLevel(double pthreatLevel) {
    threatLevel = pthreatLevel;
}

string Room::get_traps() const {
    return traps;
}

void Room::set_traps(string ptraps) {
    traps = ptraps;
}

string Room::get_type() const {
    return type;
}

void Room::set_type(std::string ptype) {
    type = ptype;
}

int Room::get_roomNumber() const {
    return roomNumber;
}

void Room::set_roomNumber(int proomNumber) {
    roomNumber = proomNumber;
}

int Room::get_doors() const {
    return doors;
}

void Room::set_doors(int pdoor) {
    doors = pdoor;
}

int Room::get_MAXDOORS() {
    return MAXDOORS;
}

int Room::get_xCoordinate() const {
    return xCoordinate;
}

void Room::set_xCoordinate(int pCoordinate) {
    xCoordinate = pCoordinate;
}

int Room::get_yCoordinate() const {
    return yCoordinate;
}

void Room::set_yCoordinate(int pCoordinate) {
    yCoordinate = pCoordinate;
}

void Room::set_Coordinates(int pX, int pY) {
    xCoordinate = pX;
    yCoordinate = pY;
}


void Room::generate_room() {
    generate_traps();

    generate_threatLevel();

    generate_treasure();

}

void Room::generate_treasure() {
    random_device rd;
    mt19937 gen(rd());
    if (threatLevel <= 0.9) {
        uniform_int_distribution<int> distributionTrea(0, 5);
        int randTreasure = distributionTrea(gen);
        treasure = randTreasure;
    } else if (threatLevel <= 1.9) {
        uniform_int_distribution<int> distributionTrea(0, 15);
        int randTreasure = distributionTrea(gen);
        treasure = randTreasure;
    } else if (threatLevel <= 2.9) {
        uniform_int_distribution<int> distributionTrea(0, 35);
        int randTreasure = distributionTrea(gen);
        treasure = randTreasure;
    } else if (threatLevel <= 3.9) {
        uniform_int_distribution<int> distributionTrea(0, 75);
        int randTreasure = distributionTrea(gen);
        randTreasure += 15;
        treasure = randTreasure;
    } else if (threatLevel <= 4.5) {
        uniform_int_distribution<int> distributionTrea(0, 150);
        int randTreasure = distributionTrea(gen);
        randTreasure += 25;
        treasure = randTreasure;
    } else if (threatLevel <= 5) {
        uniform_int_distribution<int> distributionTrea(0, 250);
        int randTreasure = distributionTrea(gen);
        randTreasure += 50;
        treasure = randTreasure;
    }
}

void Room::generate_traps() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> distribution(1, 8);
    int randTrap = distribution(gen);
    if (randTrap == 1 || randTrap == 8) {
        traps = "nothing";
    } else if (randTrap == 2) {
        traps = "nothing";
    } else if (randTrap == 3) {
        traps = "nothing";
    } else if (randTrap == 4) {
        traps = "nothing";
    } else if (randTrap == 5) {
        traps = "Hidden Pit Trap";
    } else if (randTrap == 6) {
        traps = "Hidden Pit Trap";
    } else if (randTrap == 7) {
        traps = "Hidden Pit Trap";
    }
}

void Room::generate_threatLevel() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> distributionTL(1, 50);
    int intRandTL = distributionTL(gen);
    double douRandTL = static_cast<double>(intRandTL) / 10.0;
    if (traps != "nothing" && douRandTL <= 4.6) {
        douRandTL += .5;
    } else if (douRandTL >= 4.6) {
        double x = 5 - douRandTL;
        douRandTL = douRandTL + x;
    }
    threatLevel = douRandTL;
}

void Room::generate_doors() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> distributionTL(1, MAXDOORS+1);
    int randDoor = distributionTL(gen);
    if (randDoor > MAXDOORS) {
        doors = MAXDOORS;
    } else {
        doors = randDoor;
    }
}

void Room::print() const {
    if (roomNumber > 0) {
        cout << "Room " << roomNumber << " is " << type << endl;
    } else {
        cout << "This Room is " << type << endl;
    }
    cout << "This Room's Threat Level is " << threatLevel << endl;
    cout << "This Room's total Treasure is " << treasure  << " GP" << endl;
    if (traps != "nothing") {
        cout << "This Room has " << traps << endl;
    }
    //cout << "This room has " << doors << " doors" << endl;
    cout << "Cords: (" << xCoordinate << "," << yCoordinate << ")" << endl;
}

string Room::placedMap() const {
    if (type != "Null Room") {
        return "1"; //to_string(roomNumber);
    } else {
        return "0";
    }

}
