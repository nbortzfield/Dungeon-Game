//

#include "Room_Boss.h"
using namespace std;

Room_Boss::Room_Boss() : Room() {
    MAXDOORS = 1;
    doors = 0;
    treasure = 0;
    traps = "nothing";
    threatLevel = 0;
    type = "Boss Room";
    xCoordinate = 0;
    yCoordinate = 0;
}

Room_Boss::Room_Boss(int proomNumber) : Room(proomNumber) {
    MAXDOORS = 1;
    doors = 0;
    treasure = 0;
    traps = "nothing";
    threatLevel = 0;
    type = "Boss Room";
    roomNumber = proomNumber;
    xCoordinate = 0;
    yCoordinate = 0;
}

Room_Boss::Room_Boss(int proomNumber, string ptype, double pthreatlevel, int ptreasure, string ptraps, int pdoors, int pX, int pY) {
    MAXDOORS = 1;
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

void Room_Boss::generate_treasure() {
    random_device rd;
    mt19937 gen(rd());
    if (threatLevel <= 3) {
        uniform_int_distribution<int> distributionTrea(0, 50);
        int randTreasure = distributionTrea(gen);
        randTreasure += 50;
        treasure = randTreasure;
    } else if (threatLevel <= 3.5) {
        uniform_int_distribution<int> distributionTrea(0, 75);
        int randTreasure = distributionTrea(gen);
        randTreasure += 50;
        treasure = randTreasure;
    } else if (threatLevel <= 4) {
        uniform_int_distribution<int> distributionTrea(0, 75);
        int randTreasure = distributionTrea(gen);
        randTreasure += 75;
        treasure = randTreasure;
    } else if (threatLevel <= 4.5) {
        uniform_int_distribution<int> distributionTrea(0, 100);
        int randTreasure = distributionTrea(gen);
        randTreasure += 100;
        treasure = randTreasure;
    } else if (threatLevel <= 5) {
        uniform_int_distribution<int> distributionTrea(0, 125);
        int randTreasure = distributionTrea(gen);
        randTreasure += 125;
        treasure = randTreasure;
    }
}

void Room_Boss::generate_threatLevel() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> distributionTL(30, 50);
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

void Room_Boss::generate_traps() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> distribution(1, 10);
    int randTrap = distribution(gen);
    if (randTrap == 1 || randTrap == 9 || randTrap == 10) {
        traps = "nothing";
    } else if (randTrap == 2) {
        traps = "Trapped Chest";
    } else if (randTrap == 3) {
        traps = "Simple Pit Trap";
    } else if (randTrap == 4) {
        traps = "Hidden Pit Trap";
    } else if (randTrap == 5) {
        traps = "Trapped Chest";
    } else if (randTrap == 6) {
        traps = "nothing";
    } else if (randTrap == 7) {
        traps = "nothing";
    } else if (randTrap == 8) {
        traps = "nothing";
    }
}

void Room_Boss::generate_doors() {
    doors = 1;
}