//
// Created by zacru on 2/23/2024.
//

#ifndef M2OEP_ZRUE_DUNGEON_H
#define M2OEP_ZRUE_DUNGEON_H

#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include "Room.h"
#include "Room_Hallway.h"
#include "Room_Treasure.h"
#include "Room_Boss.h"
#include "Room_Null.h"


using namespace std;

//TOM CODE
int const maxSize = 15;
//TOM CODE

class Dungeon {
protected:
    int size;
    string name;
    vector<Room> vecRooms;
    // TOM CODE v
    // This field is a 2d array that will be populated as rooms are added
    Room* dungeonMap[maxSize][maxSize];
    int height;
    int width;
    // TOM CODE ^

public:
    /**
     * Requires: Nothing
     * Modifies: size and name
     * Effects: sets size and name to default values
     */
    Dungeon();

    /**
     * @param x
     * @param y
     * Effects: checks if a room by coordinates is 0: not existant, 1: a room, or 2: a hallway
     */
    int checkRoomType(int x, int y);


    /**
     * Requires: nothing
     * Modifies: size and name
     * Effects: sets size and name to input values and runs the generate_dungeon method
     */
    explicit Dungeon(int psize, string pname);

    /**
     * Requires: nothing
     * Modifies: size
     * Effects: changes size to input
     */
    void set_size(int psize);

    /**
     * Requires: nothing
     * Modifies: nothing
     * Effects: returns size
     */
    virtual int get_size() const;

    //void set_dungeonMap_element();

    //virtual Room* get_dungeonMap_element() const;

    void clear_dungeonMap();

    /**
     * Requires: nothing
     * Modifies: height
     * Effects: changes height to input. If input >= maxSize, sets to maxSize
     */
    void set_height(int h);

    /**
     * Requires: nothing
     * Modifies: nothing
     * Effects: returns height
     */
    virtual int get_height() const;

    /**
     * Requires: nothing
     * Modifies: height
     * Effects: changes width to input. If input >= maxSize, sets to maxSize
     */
    void set_width(int w);

    /**
     * Requires: nothing
     * Modifies: nothing
     * Effects: returns width
     */
    virtual int get_width() const;

    /**
     * Requires: nothing
     * Modifies: name
     * Effects: changes name to input
     */
    void set_name(string pname);

    /**
     * Requires: nothing
     * Modifies: nothing
     * Effects: returns name
     */
    virtual string get_name() const;

    /**
     * Requires: nothing
     * Modifies: nothing
     * Effects: returns vecRooms
     */
    const vector<Room>& get_vecRooms() const;

    /**
     * Requires: nothing
     * Modifies: vecRooms
     * Effects: sets vecRooms to input
     */
    void set_vecRooms(const vector<Room>& pvecRooms);

    /**
     * Requires: nothing
     * Modifies: vecRooms
     * Effects: adds a room to vecRooms
     */
    void add_to_vecRooms(Room newRoom);

    const Room& get_room(int pRoomNumber) const;

    const Room& get_room(int pX, int pY) const;

    void set_room(Room pRoom, int pRoomNumber);

    void set_room(Room pRoom, int pX, int pY);


    /**
     * Requires: nothing
     * Modifies: vecRoom
     * Effects: clears vecRooms
     */
    void clear_vecRooms();

    /**
     * Requires: vecRooms
     * Modifies: nothing
     * Effects: calcs the total treasure from all the rooms in vecRooms
     */
    virtual int get_total_treasure() const;

    /**
     * Requires: vecRooms
     * Modifies: nothing
     * Effects: calcs the total amount of traps in vecRooms
     */
    virtual int get_total_traps() const;

    virtual int get_total_doors() const;

    /**
     * Requires: size
     * Modifies: vecRooms
     * Effects: fills vecRooms with rooms randomly assigned a room type
     */
    void generate_dungeon();

    /**
     * Requires: size
     * Modifies: vecRooms
     * Effects: fills vecRooms with rooms randomly assigned a room type
     *          Takes two int and assigns them to max room type
     */
    void generate_dungeon(int maxTreasNum, int maxBossNum);

    void generate_arrangement();

    void generate_doors();

    /**
     * Requires: nothing
     * Modifies: nothing
     * Effects: prints out brief info about the dungeon
     */
    void print() const;

    /**
     * Requires: nothing
     * Modifies: nothing
     * Effects: prints out all room info
     */
    void printRooms() const;

    /**
     * Requires: nothing
     * Modifies: nothing
     * Effects: prints out the array containing the dungeon map
     */
    void printDungeonMap() const;

    /**
     * Requires: nothing
     * Modifies: name, size, and vecRooms
     * Effects: takes in a vector of strings and assigns them to the appropriate variable
     */
    void load_dungeon_data(vector<string> saveData);

    /**
     * Requires: nothing
     * Modifies: nothing
     * Effects: returns a vector of strings with data of every appropriate variable
     */
    virtual vector<string> get_save_dungeon_data() const;

    void load_dungeon_arrangement();

    /**
     * Requires: nothing
     * Modifies: nothing
     * Effects: takes in a string and splits it into a vector of strings
     */
    virtual vector<string> split_string(const string& input, char del);

};


#endif //M2OEP_ZRUE_DUNGEON_H
