//
// Created by z on 3/21/2024.
//

#ifndef M3OEP_GGICK_TBEUCLER_ZRUE_ROOM_NULL_H
#define M3OEP_GGICK_TBEUCLER_ZRUE_ROOM_NULL_H
#include "Room.h"

class Room_Null : public Room {
    public:
        /**
         * Requires: nothing
         * Modifies: treasure, traps, threatLevel, type, roomNumber
         * Effects: Sets the protected variables with their default inputs
         */
        Room_Null();

        /**
         * Requires: roomNumber
         * Modifies: treasure, traps, threatLevel, type, roomNumber
         * Effects: Sets the protected variables with their default inputs other then roomNumber
         */
        explicit Room_Null(int proomNumber);

        /**
         * Requires: inputs for all the protected variables
         * Modifies: treasure, traps, threatLevel, type, roomNumber
         * Effects: Sets the protected variables with their inputs
         */
        explicit Room_Null(int proomNumber, string ptype, double pthreatlevel, int ptreasure, string ptraps, int pdoors, int pX, int pY);


};


#endif //M3OEP_GGICK_TBEUCLER_ZRUE_ROOM_NULL_H
