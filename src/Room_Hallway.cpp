//
// Created by zacru on 2/23/2024.
//

#include "Room_Hallway.h"
using namespace std;

Room_Hallway::Room_Hallway() : Room() {
    MAXDOORS = 6;
    doors = 0;
    treasure = 0;
    traps = "nothing";
    threatLevel = 0;
    type = "Hallway";
    roomNumber = 0;
    xCoordinate = 0;
    yCoordinate = 0;
}

Room_Hallway::Room_Hallway(int proomNumber) : Room(proomNumber) {
    MAXDOORS = 6;
    doors = 0;
    treasure = 0;
    traps = "nothing";
    threatLevel = 0;
    type = "Hallway";
    roomNumber = proomNumber;
    xCoordinate = 0;
    yCoordinate = 0;
}

Room_Hallway::Room_Hallway(int proomNumber, string ptype, double pthreatlevel, int ptreasure, string ptraps, int pdoors, int pX, int pY) : Room(
        proomNumber, ptype, pthreatlevel, ptreasure, ptraps, pdoors, pX, pY) {
    doors = pdoors;
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

void Room_Hallway::generate_treasure() {
    random_device rd;
    mt19937 gen(rd());
    if (threatLevel <= 1.9) {
        treasure = 0;
    } else if (threatLevel <= 2.9) {
        uniform_int_distribution<int> distributionTrea(0, 10);
        int randTreasure = distributionTrea(gen);
        treasure = randTreasure;
    } else if (threatLevel <= 3.5) {
        uniform_int_distribution<int> distributionTrea(0, 25);
        int randTreasure = distributionTrea(gen);
        treasure = randTreasure;
    } else if (threatLevel <= 4) {
        uniform_int_distribution<int> distributionTrea(0, 40);
        int randTreasure = distributionTrea(gen);
        treasure = randTreasure;
    }
}

void Room_Hallway::generate_threatLevel() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> distributionTL(1, 40);
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

void Room_Hallway::generate_traps() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> distribution(1, 9);
    int randTrap = distribution(gen);
    if (randTrap == 1 || randTrap == 9) {
        traps = "nothing";
    } else if (randTrap == 2) {
        traps = "Trapped Chest";
    } else if (randTrap == 3) {
        traps = "Trapped Chest";
    } else if (randTrap == 4) {
        traps = "nothing";
    } else if (randTrap == 5) {
        traps = "nothing";
    } else if (randTrap == 6) {
        traps = "nothing";
    } else if (randTrap == 7) {
        traps = "Fake Door";
    } else if (randTrap == 8) {
        traps = "nothing";
    }

}
