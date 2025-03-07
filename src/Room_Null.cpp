//
// Created by z on 3/21/2024.
//

#include "Room_Null.h"

Room_Null::Room_Null() {
    MAXDOORS = 0;
    doors = 0;
    treasure = 0;
    traps = "nothing";
    threatLevel = 0;
    type = "Null Room";
    xCoordinate = 0;
    yCoordinate = 0;
}

Room_Null::Room_Null(int proomNumber) : Room(proomNumber) {
    MAXDOORS = 0;
    doors = 0;
    treasure = 0;
    traps = "nothing";
    threatLevel = 0;
    type = "Null Room";
    roomNumber = proomNumber;
    xCoordinate = 0;
    yCoordinate = 0;
}

Room_Null::Room_Null(int proomNumber, string ptype, double pthreatlevel, int ptreasure, string ptraps, int pdoors, int pX, int pY)
        : Room(proomNumber, ptype, pthreatlevel, ptreasure, ptraps, pdoors, pX, pY) {
    MAXDOORS = 0;
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
