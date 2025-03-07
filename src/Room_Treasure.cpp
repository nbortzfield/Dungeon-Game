//

#include "Room_Treasure.h"

using namespace std;

Room_Treasure::Room_Treasure() : Room() {
    MAXDOORS = 2;
    doors = 0;
    treasure = 0;
    traps = "nothing";
    threatLevel = 0;
    type = "Treasure Room";
    roomNumber = 0;
    xCoordinate = 0;
    yCoordinate = 0;
}

Room_Treasure::Room_Treasure(int proomNumber) : Room(proomNumber) {
    MAXDOORS = 2;
    doors = 0;
    treasure = 0;
    traps = "nothing";
    threatLevel = 0;
    type = "Treasure Room";
    roomNumber = proomNumber;
    xCoordinate = 0;
    yCoordinate = 0;
}

Room_Treasure::Room_Treasure(int proomNumber, string ptype, double pthreatlevel, int ptreasure, string ptraps, int pdoors, int pX, int pY) : Room(
        proomNumber, ptype, pthreatlevel, ptreasure, ptraps, pdoors, pX, pY) {
    MAXDOORS = 2;
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

void Room_Treasure::generate_treasure() {
    random_device rd;
    mt19937 gen(rd());
    if (threatLevel <= 0.9) {
        uniform_int_distribution<int> distributionTrea(0, 50);
        int randTreasure = distributionTrea(gen);
        randTreasure += 20;
        treasure = randTreasure;
    } else if (threatLevel <= 1.9) {
        uniform_int_distribution<int> distributionTrea(0, 75);
        int randTreasure = distributionTrea(gen);
        randTreasure += 25;
        treasure = randTreasure;
    } else if (threatLevel <= 2.9) {
        uniform_int_distribution<int> distributionTrea(0, 100);
        int randTreasure = distributionTrea(gen);
        randTreasure += 50;
        treasure = randTreasure;
    } else if (threatLevel <= 3.9) {
        uniform_int_distribution<int> distributionTrea(0, 125);
        int randTreasure = distributionTrea(gen);
        randTreasure += 75;
        treasure = randTreasure;
    } else if (threatLevel <= 4.5) {
        uniform_int_distribution<int> distributionTrea(0, 175);
        int randTreasure = distributionTrea(gen);
        randTreasure += 100;
        treasure = randTreasure;
    } else if (threatLevel <= 5) {
        uniform_int_distribution<int> distributionTrea(0, 200);
        int randTreasure = distributionTrea(gen);
        randTreasure += 125;
        treasure = randTreasure;
    }
}

void Room_Treasure::generate_threatLevel() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> distributionTL(15, 50);
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

void Room_Treasure::generate_traps() {
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
        traps = "Trapped Chest";
    } else if (randTrap == 5) {
        traps = "nothing";
    } else if (randTrap == 6) {
        traps = "Cursed Item";
    } else if (randTrap == 7) {
        traps = "nothing";
    } else if (randTrap == 8) {
        traps = "nothing";
    }


}
