//
// Created by zacru on 2/21/2024.
//

#ifndef M2OEP_ZRUE_ROOM_H
#define M2OEP_ZRUE_ROOM_H
#include <vector>
#include <string>
#include <iostream>
#include <random>
#include <typeinfo>
using namespace std;

class Room {
protected:
    int MAXDOORS;
    int doors;
    int treasure;
    double threatLevel;
    string traps;
    string type; //
    int roomNumber;
    int xCoordinate;
    int yCoordinate;

public:
    /**
     * Requires: nothing
     * Modifies: treasure, traps, threatLevel, type, roomNumber
     * Effects: Sets the protected variables with their default inputs
     */
    Room();

    /**
     * Destructor
     */
    ~Room() = default;

    /**
     * Requires: roomNumber
     * Modifies: treasure, traps, threatLevel, type, roomNumber
     * Effects: Sets the protected variables with their default inputs other then roomNumber
     */
    explicit Room(int proomNumber);


    /**
     * Requires: inputs for all the protected variables
     * Modifies: treasure, traps, threatLevel, type, roomNumber
     * Effects: Sets the protected variables with their inputs
     */
    explicit Room(int proomNumber, string ptype, double pthreatlevel, int ptreasure, string ptraps, int pdoors, int pX, int pY);

     /**
      * Requires: nothing
      * Modifies: nothing
      * Effects: returns treasure
      */
    virtual int get_treasure() const;

     /**
      * Requires: nothing
      * Modifies: treasure
      * Effects: changes treasure to the input
      */
    void set_treasure(int ptreasure);

    /**
     * Requires: Nothing
     * Modifies: nothing
     * Effects: returns threat level
     */
    virtual double get_threatLevel() const;

     /**
     * Requires: nothings
     * Modifies: threat level
     * Effects: changes threat level to the input
     */
    void set_threatLevel(double pthreatLevel);


     /**
     * Requires: nothing
     * Modifies: nothing
     * Effects: returns traps
     */
    virtual string get_traps() const;

     /**
     * Requires: nothing
     * Modifies: traps
     * Effects: changes traps to the input
     */
    void set_traps(string ptraps);

    /**
     * Requires: nothing
     * Modifies: nothing
     * Effects: returns type
     */
    virtual string get_type() const;

    /**
     * Requires: nothing
     * Modifies: type
     * Effects: changes type to input
     */
    void set_type(string ptype);

    /**
     * Requires: nothing
     * Modifies: nothing
     * Effects: returns roomNumber
     */
    virtual int get_roomNumber() const;

    /**
     * Requires: nothing
     * Modifies: roomNumber
     * Effects: changes roomNumber to input
     */
    void set_roomNumber(int proomNumber);

    virtual int get_doors() const;

    void set_doors(int pdoor);

    virtual int get_MAXDOORS();

    virtual int get_xCoordinate() const;

    void set_xCoordinate(int pCoordinate);

    virtual int get_yCoordinate() const;

    void set_yCoordinate(int pCoordinate);

    void set_Coordinates(int pX, int pY);


    /**
     * Requires: generate_traps(), generate_threatLevel(), generate_treasure()
     * Modifies: nothing
     * Effects: Calls the other generate function
     */
    void generate_room();

    /**
     * Requires: threatLevel
     * Modifies: treasure
     * Effects: based on threatLevel changes treasure in random ranges
     */
    virtual void generate_treasure();

    /**
     * Requires: nothing
     * Modifies: traps
     * Effects: randomly assigns a string to traps
     */
    virtual void generate_traps();

    /**
     * Requires: traps
     * Modifies: threatLevel
     * Effects: randomly assigns a double to threatLevel, if traps is not nothing then will be larger
     */
    virtual void generate_threatLevel();

    /**
     * Requires: nothing
     * Modifies: doors
     * Effects: randomly assigns an int to doors no larger then MAXDOORS
     */
    virtual void generate_doors();

    /**
     * Requires: nothing
     * Modifies: nothing
     * Effects: prints out the room info
     */
    virtual void print() const;

    virtual string placedMap() const;

};


#endif //M2OEP_ZRUE_ROOM_H
