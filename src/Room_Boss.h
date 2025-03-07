//
// Created by zacru on 2/23/2024.
//

#ifndef M2OEP_ZRUE_ROOM_BOSS_H
#define M2OEP_ZRUE_ROOM_BOSS_H
#include "Room.h"

class Room_Boss : public Room {
public:
    /**
     * Requires: nothing
     * Modifies: treasure, traps, threatLevel, type, roomNumber
     * Effects: Sets the protected variables with their default inputs
     */
    Room_Boss();

    /**
     * Requires: roomNumber
     * Modifies: treasure, traps, threatLevel, type, roomNumber
     * Effects: Sets the protected variables with their default inputs other then roomNumber
     */
    explicit Room_Boss(int proomNumber);

    /**
     * Requires: inputs for all the protected variables
     * Modifies: treasure, traps, threatLevel, type, roomNumber
     * Effects: Sets the protected variables with their inputs
     */
    explicit Room_Boss(int proomNumber, string ptype, double pthreatlevel, int ptreasure, string ptraps, int pdoors, int pX, int pY);

    /**
     * Requires: threatLevel
     * Modifies: treasure
     * Effects: based on threatLevel changes treasure in random ranges
     */
    void generate_treasure() override;

    /**
     * Requires: nothing
     * Modifies: traps
     * Effects: randomly assigns a string to traps
     */
    void generate_traps() override;

    /**
     * Requires: traps
     * Modifies: threatLevel
     * Effects: randomly assigns a double to threatLevel, if traps is not nothing then will be larger
     */
    void generate_threatLevel() override;

    void generate_doors() override;
};


#endif //M2OEP_ZRUE_ROOM_BOSS_H
